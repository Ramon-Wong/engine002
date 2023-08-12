#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h> 
#include <math.h>

#include "matrix.h"


#define MAX_SCRIPTS	5

extern GLuint		GLSL_Program[MAX_SCRIPTS];
extern GLuint		GLSL_vertex[MAX_SCRIPTS];
extern GLuint		GLSL_fragment[MAX_SCRIPTS];
extern GLFWwindow * wnd;


extern GLfloat		Proj_Matrix[16];
extern GLfloat		View_Matrix[16];


void				Init(void);
void				Shut_Down(int);
void				Main_Loop(void);
void				Draw_Square(void);
void				Draw(void);

char *				ReadFile(const char *);
void				ShaderSetup();

#endif
