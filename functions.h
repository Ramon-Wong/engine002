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
typedef float32_t           float32;    

// 3D vector
typedef struct {            float32_t DATA[3];}     VECTOR3D;

// Matrix 4x4
typedef struct {            float32_t DATA[16];}    MATRIX4X4;


#endif