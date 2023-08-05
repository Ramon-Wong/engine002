#include "functions.h"




VECTOR3D normalize( VECTOR3D v ) {

    float length = sqrt( v.x*v.x + v.y*v.y + v.z*v.z );
    VECTOR3D result = { v.x/length, v.y/length, v.z/length };

    return result;
}


VECTOR3D crossproduct( VECTOR3D v1, VECTOR3D v2 ) {
    VECTOR3D result;
    result.x = v1.y*v2.z - v1.z*v2.y; 
    result.y = v1.z*v2.x - v1.x*v2.z; 
    result.z = v1.x*v2.y - v1.y*v2.x;
    return result;
}


float dotProduct( VECTOR3D v1, VECTOR3D v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


void LookAtM( MATRIX4X * Result, VECTOR3D * View, VECTOR3D * Pose, VECTOR3D * UpVx){
    VECTOR3D X, Y, Z;
    Z = normalize( *View - *Pose );
    X = normalize( crossproduct( *UpVx, Z ));
    Y = normalize( crossproduct( Z, X ));

    Result->DATA[0] = X.x;  Result->DATA[4] = X.y;  Result->DATA[8]     = X.z; // Result->DATA[12]     = -dotProduct( X, View );
    Result->DATA[1] = Y.x;  Result->DATA[5] = Y.y;  Result->DATA[9]     = Y.z; // Result->DATA[13]     = -dotProduct( Y, View );
    Result->DATA[2] = Z.x;  Result->DATA[6] = Z.y;  Result->DATA[10]    = Z.z; // Result->DATA[14]     = -dotProduct( Z, View );
    Result->DATA[3] = 0.0;  Result->DATA[7] = 0.0;  Result->DATA[11]    = 0.0; // Result->DATA[15]     = 1.0;
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