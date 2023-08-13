#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


extern GLuint		GLSL_Program;
extern GLuint		GLSL_vertex;
extern GLuint		GLSL_fragment;

void                Init(const GLint, const GLint, const char *);
void                Shutdown(int);
void                ShaderSetup( const char *, const char *);

#endif