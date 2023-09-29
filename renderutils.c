#include "functions.h"


static float	    CulRTMatrix[16];
static int		    counter = 0;


void gMatrixRotation( GLfloat angle, GLfloat x, GLfloat y, GLfloat z){

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


void gMatrixTranslation( GLfloat x, GLfloat y, GLfloat z){

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

    glUniformMatrix4fv( glGetUniformLocation( Prog, uniform), 1, GL_FALSE, CulRTMatrix);
	counter = 0;
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


void RotateCamera(float* Pose, float* View, float angle, float x, float y, float z){
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

    float newView[3];
    newView[0] = rotationMatrix[0] * (View[0] - Pose[0]) + rotationMatrix[1] * (View[1] - Pose[1]) + rotationMatrix[2] * (View[2] - Pose[2]);
    newView[1] = rotationMatrix[3] * (View[0] - Pose[0]) + rotationMatrix[4] * (View[1] - Pose[1]) + rotationMatrix[5] * (View[2] - Pose[2]);
    newView[2] = rotationMatrix[6] * (View[0] - Pose[0]) + rotationMatrix[7] * (View[1] - Pose[1]) + rotationMatrix[8] * (View[2] - Pose[2]);

    // Update the new view vector.
    View[0] = Pose[0] + newView[0];
    View[1] = Pose[1] + newView[1];
    View[2] = Pose[2] + newView[2];
}



void StrafeCamera(float* Pose, float* View, float speed){
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
