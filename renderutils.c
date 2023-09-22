#include "functions.h"


static float gFrustum[6][4];



void NormalizePlane(int side){

	float magnitude = (float)sqrt( gFrustum[side][0] * gFrustum[side][0] + gFrustum[side][1] * gFrustum[side][1] + gFrustum[side][2] * gFrustum[side][2] );

	gFrustum[side][0] /= magnitude;
	gFrustum[side][1] /= magnitude;
	gFrustum[side][2] /= magnitude;
	gFrustum[side][3] /= magnitude; 
}


void setPlanes( float * ProjView){

	gFrustum[RIGHT][0]      = ProjView[ 3] - ProjView[ 0];
	gFrustum[RIGHT][1]      = ProjView[ 7] - ProjView[ 4];
	gFrustum[RIGHT][2]      = ProjView[11] - ProjView[ 8];
	gFrustum[RIGHT][3]      = ProjView[15] - ProjView[12];
    NormalizePlane(RIGHT);

	gFrustum[LEFT][0]       = ProjView[ 3] + ProjView[ 0];
	gFrustum[LEFT][1]       = ProjView[ 7] + ProjView[ 4];
	gFrustum[LEFT][2]       = ProjView[11] + ProjView[ 8];
	gFrustum[LEFT][3]       = ProjView[15] + ProjView[12];
    NormalizePlane(LEFT);

	gFrustum[BOTTOM][0]     = ProjView[ 3] + ProjView[ 1];
	gFrustum[BOTTOM][1]     = ProjView[ 7] + ProjView[ 5];
	gFrustum[BOTTOM][2]     = ProjView[11] + ProjView[ 9];
	gFrustum[BOTTOM][3]     = ProjView[15] + ProjView[13];
    NormalizePlane(BOTTOM);

	gFrustum[TOP][0]        = ProjView[ 3] - ProjView[ 1];
	gFrustum[TOP][1]        = ProjView[ 7] - ProjView[ 5];
	gFrustum[TOP][2]        = ProjView[11] - ProjView[ 9];
	gFrustum[TOP][3]        = ProjView[15] - ProjView[13];    
    NormalizePlane(TOP);

    gFrustum[BACK][0]       = ProjView[ 3] - ProjView[ 2];
	gFrustum[BACK][1]       = ProjView[ 7] - ProjView[ 6];
	gFrustum[BACK][2]       = ProjView[11] - ProjView[10];
	gFrustum[BACK][3]       = ProjView[15] - ProjView[14];
    NormalizePlane(BACK);

	gFrustum[FRONT][0]      = ProjView[ 3] + ProjView[ 2];
	gFrustum[FRONT][1]      = ProjView[ 7] + ProjView[ 6];
	gFrustum[FRONT][2]      = ProjView[11] + ProjView[10];
	gFrustum[FRONT][3]      = ProjView[15] + ProjView[14];    
    NormalizePlane(FRONT);
}


int PointinFrustum(float * vec){
	for(int i = 0; i < 6; i++ ){
		if( gFrustum[i][0] * vec[0] + gFrustum[i][1] * vec[1] + gFrustum[i][2] * vec[3] + m_Frustum[i][3] <= 0){
			return 0;           // not in frustum
		}
    }
    return 1;
}


void Draw_Object( GLuint array_buffer, int size){
	glBindVertexArray( array_buffer);
	glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
    // Draw your geometry
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_BYTE, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}


static float	CulRTMatrix[16];
static int		counter = 0;

void gMatrixRotation( GLuint Prog, GLfloat angle, GLfloat x, GLfloat y, GLfloat z){

    float Temp[16];

	if( counter == 0){
		MLoadIdentity( CulRTMatrix);
        MRotate( CulRTMatrix, angle, x, y, z);
	}else if( counter > 0){
        MLoadIdentity( Temp);
        MRotate( Temp, angle, x, y, z);
        MMultiply( CulRTMatrix, CulRTMatrix, Temp);
    }

    counter += 1;
}


void gMatrixTranslation( GLuint Prog, GLfloat x, GLfloat y, GLfloat z){

    float Temp[16];

	if( counter == 0){
		MLoadIdentity( CulRTMatrix);
        MTranslate( CulRTMatrix, x, y, z);
	}else if( counter > 0){
        MLoadIdentity( Temp);
        MTranslate( CulRTMatrix, x, y, z);
        MMultiply( CulRTMatrix, CulRTMatrix, Temp);
    }

    counter += 1;
}


void gPopMatrix(GLuint Prog, const char * uniform){

	// push stuf to the shader program
    glUniformMatrix4fv( glGetUniformLocation( Prog, uniform), 1, GL_FALSE, CulRTMatrix);
	MLoadIdentity(CulRTMatrix);
	counter = 0;
}


void MoveCamera(float * Pose, float * View, float speed){
    float vVector[3];

    vVector[0]  = View[0] - Pose[0];    // x
    vVector[1]  = View[1] - Pose[1];    // y, just in case
    vVector[2]  = View[2] - Pose[2];    // z
	
    Pose[0] += vVector[0] * speed; 
    Pose[2] += vVector[2] * speed; 

    View[0] += vVector[0] * speed; 
    View[2] += vVector[2] * speed; 
}


// void RotateCamera(float * Pose, float * View, float angle, float x, float y, float z){
//     float nVector[3];
//     float vVector[3];

//     vVector[0]  = View[0] - Pose[0];    // x
//     vVector[1]  = View[1] - Pose[1];    // y, just in case
//     vVector[2]  = View[2] - Pose[2];    // z

// 	float cosTheta = (float)cos(angle);
// 	float sinTheta = (float)sin(angle);

// 	nVector[0]   = (cosTheta + (1 - cosTheta) * x * x)		* vVector[0];
// 	nVector[0]  += ((1 - cosTheta) * x * y - z * sinTheta)	* vVector[1];
// 	nVector[0]  += ((1 - cosTheta) * x * z + y * sinTheta)	* vVector[2];

// 	nVector[1]   = ((1 - cosTheta) * x * y + z * sinTheta)	* vVector[0];
// 	nVector[1]  += (cosTheta + (1 - cosTheta) * y * y)		* vVector[1];
// 	nVector[1]  += ((1 - cosTheta) * y * z - x * sinTheta)	* vVector[2];

// 	nVector[2]  = ((1 - cosTheta) * x * z - y * sinTheta)	* vVector[0];
// 	nVector[2] += ((1 - cosTheta) * y * z + x * sinTheta)	* vVector[1];
// 	nVector[2] += (cosTheta + (1 - cosTheta) * z * z)		* vVector[2];

//     View[0] = Pose[0] + nVector[0];
//     View[1] = Pose[1] + nVector[1];
//     View[2] = Pose[2] + nVector[2];
// }


void RotateCamera(float* Pose, float* View, float angle, float x, float y, float z) {
    // Calculate the rotation matrix.
    float cosTheta = cos(angle);
    float sinTheta = sin(angle);

    // Create the rotation matrix for the specified axis (x, y, z).
    float rotationMatrix[9];
    rotationMatrix[0] = cosTheta + (1 - cosTheta) * x * x;
    rotationMatrix[1] = (1 - cosTheta) * x * y - z * sinTheta;
    rotationMatrix[2] = (1 - cosTheta) * x * z + y * sinTheta;
    rotationMatrix[3] = (1 - cosTheta) * x * y + z * sinTheta;
    rotationMatrix[4] = cosTheta + (1 - cosTheta) * y * y;
    rotationMatrix[5] = (1 - cosTheta) * y * z - x * sinTheta;
    rotationMatrix[6] = (1 - cosTheta) * x * z - y * sinTheta;
    rotationMatrix[7] = (1 - cosTheta) * y * z + x * sinTheta;
    rotationMatrix[8] = cosTheta + (1 - cosTheta) * z * z;

    // Apply the rotation matrix to the view vector.
    float newView[3];
    newView[0] = rotationMatrix[0] * (View[0] - Pose[0]) + rotationMatrix[1] * (View[1] - Pose[1]) + rotationMatrix[2] * (View[2] - Pose[2]);
    newView[1] = rotationMatrix[3] * (View[0] - Pose[0]) + rotationMatrix[4] * (View[1] - Pose[1]) + rotationMatrix[5] * (View[2] - Pose[2]);
    newView[2] = rotationMatrix[6] * (View[0] - Pose[0]) + rotationMatrix[7] * (View[1] - Pose[1]) + rotationMatrix[8] * (View[2] - Pose[2]);

    // Update the new view vector.
    View[0] = Pose[0] + newView[0];
    View[1] = Pose[1] + newView[1];
    View[2] = Pose[2] + newView[2];
}



void StrafeCamera(float* Pose, float* View, float speed) {
    // Calculate the forward vector (view - pose).
    float forward[3];
    forward[0] = View[0] - Pose[0];
    forward[1] = View[1] - Pose[1];
    forward[2] = View[2] - Pose[2];

    // Calculate the right (strafe) direction using the cross product of forward and the up vector.
    float up[3] = {0.0f, 1.0f, 0.0f};  // Assuming up is in the positive Y direction.
    float right[3];
    CrossProduct(right, forward, up);
    Normalize(right);

    // Update the camera's position and view based on the right vector and speed.
    Pose[0] += right[0] * speed;
    Pose[2] += right[2] * speed;
    View[0] += right[0] * speed;
    View[2] += right[2] * speed;
}
