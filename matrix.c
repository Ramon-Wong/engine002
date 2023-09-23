#include "matrix.h"
#include <stdio.h>


void MLoadIdentity(float * mat){
	float M[16] = { 1.0, 0.0, 0.0, 0.0,
					0.0, 1.0, 0.0, 0.0,
					0.0, 0.0, 1.0, 0.0,
					0.0, 0.0, 0.0, 1.0 };
	
	memcpy( mat, M, sizeof(float[16]));
}


void MFrustum(float * Mat, float Left, float Right, float Bottom, float Top, float Near, float Far){
	float RL = 1 / (Right - Left);
	float TB = 1 / (Top - Bottom);
	float NF = 1 / (Near - Far);
	
	Mat[0] = (Near * 2) * RL;
	Mat[1] = 0.0f;
	Mat[2] = 0.0f;
	Mat[3] = 0.0f;
	Mat[4] = 0.0f;
	Mat[5] = (Near * 2) * TB;
	Mat[6] = 0.0f;
	Mat[7] = 0.0f;
	Mat[8] = (Right + Left) * RL;
	Mat[9] = (Top + Bottom) * TB;
	Mat[10] = (Far + Near) * NF;
	Mat[11] = -1.0f;
	Mat[12] = 0.0f;
	Mat[13] = 0.0f;
	Mat[14] = (Far * Near * 2) * NF;
	Mat[15] = 0.0f;
}


void LookAtM( float * Mat, float * Pose, float * View, float * UpVx){
	float X[3], Y[3], Z[3];
	Z[0] = View[0] - Pose[0];
	Z[1] = View[1] - Pose[1];
	Z[2] = View[2] - Pose[2];
	Normalize(Z);
	
	CrossProduct( X, UpVx, Z); // Compute cross product of UpVx, Z
	Normalize(X);
	
	CrossProduct( Y, Z, X); // reCompute vector Y
	Normalize(Y);
	
	Mat[0]	= X[0];	Mat[4]	= X[1];	Mat[8]	= X[2];	Mat[12]	= -dotproduct( X, View );
	Mat[1]	= Y[0];	Mat[5]	= Y[1];	Mat[9]	= Y[2]; Mat[13]	= -dotproduct( Y, View );
	Mat[2]	= Z[0];	Mat[6]	= Z[1];	Mat[10] = Z[2]; Mat[14]	= -dotproduct( Z, View );
	Mat[3]	= 0.0;	Mat[7]	= 0.0;	Mat[11] = 0.0;	Mat[15]	= 1.0;	
}


void MTranslate(float * Result, float x, float y, float z){
	Result[12] += (Result[0] * x + Result[4] * y + Result[8] * z);
	Result[13] += (Result[1] * x + Result[5] * y + Result[9] * z);
	Result[14] += (Result[2] * x + Result[6] * y + Result[10] * z);
	Result[15] += (Result[3] * x + Result[7] * y + Result[11] * z);
}


void MRotate(float * Mat, float angle, float x, float y, float z){
	
	angle = angle * PI / 180.0f;
	float s = sin(angle);
	float c = cos(angle);
	float t = 1.0f - c;
	
	float tx = t * x;	float ty = t * y;	float tz = t * z;
	float sz = s * z;	float sy = s * y;	float sx = s * x;
	
	Mat[0]  = tx * x + c;	Mat[4]  = tx * y - sz;	Mat[8]  = tx * z + sy;	Mat[12] = 0;
	Mat[1]  = tx * y + sz;	Mat[5]  = ty * y + c;	Mat[9]  = ty * z - sx;	Mat[13] = 0; 
	Mat[2]  = tx * z - sy;	Mat[6]  = ty * z + sx;	Mat[10] = tz * z + c;	Mat[14] = 0;
	Mat[3]  = 0;			Mat[7]  = 0;			Mat[11] = 0;			Mat[15] = 1; 
}


void CrossProduct(float * Result, float * Vec1, float * Vec2){
	Result[0] = Vec1[1] * Vec2[2] - Vec1[2] * Vec2[1];
	Result[1] = Vec1[2] * Vec2[0] - Vec1[0] * Vec2[2];
	Result[2] = Vec1[0] * Vec2[1] - Vec1[1] * Vec2[0];
}


void Normalize(float * Vec){
	float Magnitude = sqrt(Vec[0] * Vec[0] + Vec[1] * Vec[1] + Vec[2] * Vec[2]);
	
	Vec[0] /= Magnitude;
	Vec[1] /= Magnitude;
	Vec[2] /= Magnitude;
}


void MMultiply(float * Mat, float * Mat1, float * Mat2){
	int i;
	float Result[16];

	for(i = 0; i < 4; i++){
		Result[i * 4] 		= (Mat2[i*4] * Mat1[0]) + (Mat2[i*4+1] * Mat1[4]) + (Mat2[i*4+2] * Mat1[8]) + (Mat2[i*4+3] * Mat1[12]);
		Result[i * 4 + 1]	= (Mat2[i*4] * Mat1[1]) + (Mat2[i*4+1] * Mat1[5]) + (Mat2[i*4+2] * Mat1[9]) + (Mat2[i*4+3] * Mat1[13]);
		Result[i * 4 + 2]	= (Mat2[i*4] * Mat1[2]) + (Mat2[i*4+1] * Mat1[6]) + (Mat2[i*4+2] * Mat1[10]) + (Mat2[i*4+3] * Mat1[14]);
		Result[i * 4 + 3]	= (Mat2[i*4] * Mat1[3]) + (Mat2[i*4+1] * Mat1[7]) + (Mat2[i*4+2] * Mat1[11]) + (Mat2[i*4+3] * Mat1[15]);
	}
	memcpy(Mat, Result, sizeof(float[16]));
}


void MTransform(float * Result, float * Data, float * Vec){
	
	Result[0] = Vec[0]*Data[0] + Vec[1]*Data[4] + Vec[2]*Data[8]  + Data[12];
	Result[1] = Vec[0]*Data[1] + Vec[1]*Data[5] + Vec[2]*Data[9]  + Data[13];
	Result[2] = Vec[0]*Data[2] + Vec[1]*Data[6] + Vec[2]*Data[10] + Data[14];
	Result[3] = Vec[0]*Data[3] + Vec[1]*Data[7] + Vec[2]*Data[11] + Data[15];
}


float dotproduct( float * V1, float * V2){
	return V1[0] * V2[0] + V1[1] * V2[1] + V1[2] * V2[2];
}


void MVectorMultiply( float * result, float * Mat, float * Vec){
    result[0] = Mat[0] * Vec[0] + Mat[4] * Vec[1] + Mat[8]  * Vec[2] + Mat[12];
    result[1] = Mat[1] * Vec[0] + Mat[5] * Vec[1] + Mat[9]  * Vec[2] + Mat[13];
    result[2] = Mat[2] * Vec[0] + Mat[6] * Vec[1] + Mat[10] * Vec[2] + Mat[14];	
}