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
float           dotproduct(VECTOR3D, VECTOR3D);

void            LookAtM( MATRIX4X *, VECTOR3D *, VECTOR3D *, VECTOR3D *);
void            MFrustum( float *, float, float, float, float, float, float);

// Matrix 4x4
struct MATRIX4X{

    MATRIX4X( float * data ) {
        memcpy( DATA, data, sizeof(float) * 16 );
    }
    float DATA[16];
};

#endif



