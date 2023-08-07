#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GL/glfw.h>



extern GLuint		GLSL_Program;
extern GLuint		GLSL_vertex;
extern GLuint		GLSL_fragment;

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