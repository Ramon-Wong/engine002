#ifndef _MATRIX_H
#define _MATRIX_H

#include "functions.h"

#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286


void	MLoadIdentity(MATRIX4X *);                                                    // Load the identity matrix
// void	MFrustum(GLfloat *, GLfloat, GLfloat, GLfloat, GLfloat,/ GLfloat, GLfloat);  // Frustum Matrix, Result, Left, Right, Bottom, Top, Near, Far

void	MTranslate( float *, float, float, float);                                  // Translation Matrix, Result, x, y, z
void	CrossProduct( float *, float *, float *);                                   // Cross Product, Result, Vector 1, Vector 2 
void	Normalize( float *);                                                        // Normalize, Vector   

void	LookAtM( float *, float *, float *, float *);                               // Camera Matrix, Result, position, target, up vector

// void	MMultiply(GLfloat *, GLfloat *, GLfloat *);                                 // Multiply, Result, Matrix 1, Matrix 2
// void	MTransform(GLfloat *, GLfloat *, GLfloat *);                                // Transform, Result, Matrix, Vector


#endif
