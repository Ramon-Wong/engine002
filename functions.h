#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <GLFW/glfw3.h>
#include <GL/glu.h>

#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

extern GLuint		GLSL_Program;
extern GLuint		GLSL_vertex;
extern GLuint		GLSL_fragment;

extern GLfloat		Proj_Matrix[16];
extern GLfloat		View_Matrix[16];

char            *	ReadFile(const char *);
void                ShaderSetup();
void                Init(void);
void                Draw(void);
void                Shutdown(int);

void                SizeOpenGLScreen( int, int);
void                gloadTexture( GLuint *, unsigned char *, int, int, int);

#endif