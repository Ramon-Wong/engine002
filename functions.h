#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h> 
#include <math.h>

#include "matrix.h"


extern GLuint		GLSL_Program;
extern GLuint		GLSL_Fbo;
extern GLuint		GLSL_vertex;
extern GLuint		GLSL_fragment;
extern GLFWwindow * wnd;


extern GLfloat		Proj_Matrix[16];
extern GLfloat		View_Matrix[16];


void				Init(void);
void				Shut_Down(int);
void				Main_Loop(void);

void				ShaderSetup(const char *, const char *);
void                CreateTexture( GLenum, GLuint *, unsigned char *, int, int, GLenum, GLenum);

void                SetupVAO( GLuint *, GLuint *, GLuint *, GLfloat *, GLfloat *, GLubyte *, GLsizei, GLsizei, GLsizei);
void                SetupVAOArray( GLuint *, GLuint *, GLuint *, GLfloat *, GLfloat *, GLfloat *, GLubyte *, GLsizei, GLsizei, GLsizei, GLsizei);

#endif
