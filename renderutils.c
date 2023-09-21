#include "functions.h"




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


void RotateCamera(float * Pose, float * View, float angle, float x, float y, float z){
    float nVector[3];
    float vVector[3];

    vVector[0]  = View[0] - Pose[0];    // x
    vVector[1]  = View[1] - Pose[1];    // y, just in case
    vVector[2]  = View[2] - Pose[2];    // z

	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	nVector[0]   = (cosTheta + (1 - cosTheta) * x * x)		* vVector[0];
	nVector[0]  += ((1 - cosTheta) * x * y - z * sinTheta)	* vVector[1];
	nVector[0]  += ((1 - cosTheta) * x * z + y * sinTheta)	* vVector[2];

	nVector[1]   = ((1 - cosTheta) * x * y + z * sinTheta)	* vVector[0];
	nVector[1]  += (cosTheta + (1 - cosTheta) * y * y)		* vVector[1];
	nVector[1]  += ((1 - cosTheta) * y * z - x * sinTheta)	* vVector[2];

	nVector[2]  = ((1 - cosTheta) * x * z - y * sinTheta)	* vVector[0];
	nVector[2] += ((1 - cosTheta) * y * z + x * sinTheta)	* vVector[1];
	nVector[2] += (cosTheta + (1 - cosTheta) * z * z)		* vVector[2];

    View[0] = Pose[0] + nVector[0];
    View[1] = Pose[1] + nVector[1];
    View[2] = Pose[2] + nVector[2];
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
