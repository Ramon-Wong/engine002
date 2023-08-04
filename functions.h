#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <assert.h>
#include <string.h>
#include <math.h>

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

    VECTOR3D( float x, float y, float z ) : x(x), y(y), z(z) {}

    VECTOR3D operator =( const VECTOR3D & v ) const {
        return VECTOR3D( v.x, v.y, v.z );
    }

    VECTOR3D operator+( const VECTOR3D & v ) const {
        return VECTOR3D( x + v.x, y + v.y, z + v.z );
    }

    VECTOR3D operator-( const VECTOR3D & v ) const {
        return VECTOR3D( x - v.x, y - v.y, z - v.z );
    }


};

// Matrix 4x4
struct MATRIX4X{

    MATRIX4X( float * data ) {
        memcpy( DATA, data, sizeof(float) * 16 );
    }
    float DATA[16];
};


#endif