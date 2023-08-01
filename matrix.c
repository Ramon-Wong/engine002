#include "matrix.h"
#include <stdio.h>





void MLoadIdentity(MATRIX4X * mat){
	mat->DATA[0]	= 1.0f;	mat->DATA[1]	= 0.0f;	mat->DATA[2]	= 0.0f;	mat->DATA[3]	= 0.0f;
	mat->DATA[4]	= 0.0f;	mat->DATA[5]	= 1.0f;	mat->DATA[6]	= 0.0f;	mat->DATA[7]	= 0.0f;
	mat->DATA[8]	= 0.0f;	mat->DATA[9]	= 0.0f;	mat->DATA[10]	= 1.0f;	mat->DATA[11]	= 0.0f;
	mat->DATA[12]	= 0.0f;	mat->DATA[13]	= 0.0f;	mat->DATA[14]	= 0.0f;	mat->DATA[15]	= 1.0f;
}


void Normalize( VECTOR3D * Vec){
	float Magnitude = sqrt( Vec->DATA[0] * Vec->DATA[0] + Vec->DATA[1] * Vec->DATA[1] + Vec->DATA[2] * Vec->DATA[2]);
	
	Vec->DATA[0] /= Magnitude;
	Vec->DATA[1] /= Magnitude;
	Vec->DATA[2] /= Magnitude;
}


void CrossProduct( VECTOR3D * Result, VECTOR3D * Vec1, VECTOR3D * Vec2){
	Result->DATA[0] = Vec1->DATA[1] * Vec2->DATA[2] - Vec1->DATA[2] * Vec2->DATA[1];
	Result->DATA[1] = Vec1->DATA[2] * Vec2->DATA[0] - Vec1->DATA[0] * Vec2->DATA[2];
	Result->DATA[2] = Vec1->DATA[0] * Vec2->DATA[1] - Vec1->DATA[1] * Vec2->DATA[0];
}


void MTranslate( MATRIX4X * Result, float x, float y, float z){

	Result->DATA[12] += ( Result->DATA[0] * x + Result->DATA[4] * y + Result->DATA[8]	* z);
	Result->DATA[13] += ( Result->DATA[1] * x + Result->DATA[5] * y + Result->DATA[9]	* z);
	Result->DATA[14] += ( Result->DATA[2] * x + Result->DATA[6] * y + Result->DATA[10]	* z);
	Result->DATA[15] += ( Result->DATA[3] * x + Result->DATA[7] * y + Result->DATA[11]	* z);

}




// void MFrustum(GLfloat * Mat, GLfloat Left, GLfloat Right, GLfloat Bottom, GLfloat Top, GLfloat Near, GLfloat Far){
// 	GLfloat RL = 1 / (Right - Left);
// 	GLfloat TB = 1 / (Top - Bottom);
// 	GLfloat NF = 1 / (Near - Far);
	
// 	Mat[0] = (Near * 2) * RL;
// 	Mat[1] = 0.0f;
// 	Mat[2] = 0.0f;
// 	Mat[3] = 0.0f;
// 	Mat[4] = 0.0f;
// 	Mat[5] = (Near * 2) * TB;
// 	Mat[6] = 0.0f;
// 	Mat[7] = 0.0f;
// 	Mat[8] = (Right + Left) * RL;
// 	Mat[9] = (Top + Bottom) * TB;
// 	Mat[10] = (Far + Near) * NF;
// 	Mat[11] = -1.0f;
// 	Mat[12] = 0.0f;
// 	Mat[13] = 0.0f;
// 	Mat[14] = (Far * Near * 2) * NF;
// 	Mat[15] = 0.0f;
// }


// void LookAtM( GLfloat * Mat, GLfloat * Pose, GLfloat * View, GLfloat * UpVx){
// 	GLfloat X[3], Y[3], Z[3];
// 	Z[0] = View[0] - Pose[0];
// 	Z[1] = View[1] - Pose[1];
// 	Z[2] = View[2] - Pose[2];
// 	Normalize(Z);
	
// 	CrossProduct( X, UpVx, Z);      // Compute cross product of UpVx, Z
// 	Normalize(X);
	
// 	CrossProduct( Y, Z, X);         // reCompute vector Y
// 	Normalize(Y);
	
// 	Mat[0] = X[0];	Mat[4] = X[1];	Mat[8] = X[2];
// 	Mat[1] = Y[0];	Mat[5] = Y[1];	Mat[9] = Y[2];
// 	Mat[2] = Z[0];	Mat[6] = Z[1];	Mat[10] = Z[2];
// 	Mat[3] = 0.0;	Mat[7] = 0.0;	Mat[11] = 0.0;
	
// 	MTranslate( Mat, -View[0], -View[1], -View[2]);
// }



// void MTransform(GLfloat * Result, GLfloat * Data, GLfloat * Vec){
	
// 	Result[0] = Vec[0]*Data[0] + Vec[1]*Data[4] + Vec[2]*Data[8]  + Data[12];
// 	Result[1] = Vec[0]*Data[1] + Vec[1]*Data[5] + Vec[2]*Data[9]  + Data[13];
// 	Result[2] = Vec[0]*Data[2] + Vec[1]*Data[6] + Vec[2]*Data[10] + Data[14];
// 	Result[3] = Vec[0]*Data[3] + Vec[1]*Data[7] + Vec[2]*Data[11] + Data[15];
// }


// void MMultiply(GLfloat * Mat, GLfloat * Mat1, GLfloat * Mat2){
// 	int i;
// 	GLfloat Result[16];

// 	for(i = 0; i < 4; i++){
// 		Result[i * 4] = (Mat2[i*4] * Mat1[0]) + (Mat2[i*4+1] * Mat1[4]) + (Mat2[i*4+2] * Mat1[8]) + (Mat2[i*4+3] * Mat1[12]);
// 		Result[i * 4 + 1] = (Mat2[i*4] * Mat1[1]) + (Mat2[i*4+1] * Mat1[5]) + (Mat2[i*4+2] * Mat1[9]) + (Mat2[i*4+3] * Mat1[13]);
// 		Result[i * 4 + 2] = (Mat2[i*4] * Mat1[2]) + (Mat2[i*4+1] * Mat1[6]) + (Mat2[i*4+2] * Mat1[10]) + (Mat2[i*4+3] * Mat1[14]);
// 		Result[i * 4 + 3] = (Mat2[i*4] * Mat1[3]) + (Mat2[i*4+1] * Mat1[7]) + (Mat2[i*4+2] * Mat1[11]) + (Mat2[i*4+3] * Mat1[15]);
// 	}
// 	memcpy(Mat, Result, sizeof(GLfloat[16]));
// }











