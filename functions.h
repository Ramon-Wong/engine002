#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <assert.h>
#include <string.h>
#include <math.h>

#include <GL/glew.h>
#include <GL/glfw.h>

// Function prototypes
// uint8_t/int8_t equals to unsigned/signed char
// uint16_t/int16_t equals to unsigned/signed short
// uint32_t/int32_t equals to unsigned/signed int

//I need some interesting sounding names for these types
typedef int8_t              int8;
typedef int16_t             int16; 
typedef int32_t             int32;

// 3D vector
struct VECTOR3D{
    
    float x;
    float y;
    float z;
    
    VECTOR3D() : x(0), y(0), z(0) {}
    VECTOR3D( float x, float y, float z ){ this->x = x; this->y = y; this->z = z; }

    // Normalize the vector
    VECTOR3D operator = (const VECTOR3D& v ){   x = v.x;  y = v.y;  z = v.z;  return *this;}
    VECTOR3D operator + (const VECTOR3D& v ){   return VECTOR3D( x + v.x, y + v.y, z + v.z ); }
    VECTOR3D operator - (const VECTOR3D& v ){   return VECTOR3D( x - v.x, y - v.y, z - v.z ); }

};

VECTOR3D        normalize(VECTOR3D);
VECTOR3D        crossproduct(VECTOR3D, VECTOR3D);



// Matrix 4x4
struct MATRIX4X{

    MATRIX4X( float * data ) {
        memcpy( DATA, data, sizeof(float) * 16 );
    }
    float DATA[16];
};

#endif




// void LookAtM( float * Result, float * Pose, float * View, float * UpVx){
// 	float X[3], Y[3], Z[3];
// 	Z[0] = View[0] - Pose[0];
// 	Z[1] = View[1] - Pose[1];
// 	Z[2] = View[2] - Pose[2];
// 	Normalize(Z);
	
// 	CrossProduct( X, UpVx, Z);      // Compute cross product of UpVx, Z
// 	Normalize(X);
	
// 	CrossProduct( Y, Z, X);         // reCompute vector Y
// 	Normalize(Y);
	
// 	Result[0] = X[0];	Result[4] = X[1];	Result[8] = X[2];
// 	Result[1] = Y[0];	Result[5] = Y[1];	Result[9] = Y[2];
// 	Result[2] = Z[0];	Result[6] = Z[1];	Result[10] = Z[2];
// 	Result[3] = 0.0;	Result[7] = 0.0;	Result[11] = 0.0;
	
// 	MTranslate( Result, -View[0], -View[1], -View[2]);
// }