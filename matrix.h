#ifndef _MATRIX_H
#define _MATRIX_H

#include <assert.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286


void	MLoadIdentity(float*);
void	MFrustum(float *, float, float, float, float, float, float);
void	LookAtM( float *, float *, float *, float *);

void	MTranslate(float *, float, float, float);
void	CrossProduct(float *, float *, float *);
void	Normalize(float *);

void	MMultiply(float *, float *, float *);
void	MTransform(float *, float *, float *);


#endif
