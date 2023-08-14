#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h> 
#include <math.h>

#include "matrix.h"


extern GLuint		GLSL_Program;
extern GLuint		GLSL_vertex;
extern GLuint		GLSL_fragment;
extern GLFWwindow * wnd;


extern GLfloat		Proj_Matrix[16];
extern GLfloat		View_Matrix[16];


void				Init(void);
void				Shut_Down(int);
void				Main_Loop(void);

void				ShaderSetup(const char *, const char *);

#endif
