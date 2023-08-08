#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <assert.h>
#include <string.h>
#include <math.h>

#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>


extern GLuint		GLSL_Program;
extern GLuint		GLSL_vertex;
extern GLuint		GLSL_fragment;

extern GLfloat		Proj_Matrix[16];
extern GLfloat		View_Matrix[16];

void                Init();
void                Shutdown(int);
void				Main_Loop(GLFWwindow *);




#endif