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



extern GLuint		GLSL_Fbo;
extern GLFWwindow * wnd;

extern GLfloat      box_vertices[24];
extern GLfloat      box_normals[72];
extern GLfloat      box_colors[72];
extern GLfloat      box_texcoords[48];
extern GLubyte      box_indices[36];

void				Init(void);
void				Shut_Down(int);
void				Main_Loop(void);

void				ShaderSetup(const char *, const char *);
void				ShaderSetup1(void);
void				ShaderSetup2(const char *, const char *, GLuint, GLuint, GLuint);

GLuint				ReadGLSLScript(GLuint, uint, const char *);
void				LinkPrograms(GLuint);

void                CreateTexture( GLenum, GLuint *, unsigned char *, int, int, GLenum);
GLuint              LoadTexture( GLuint, const char *, const char *, int);

void                gMatrixRotation( GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
void                gPopMatrix(GLuint, const char *);

void                SetupVAO( GLuint *, GLuint *, GLuint *, GLfloat *, GLfloat *, GLubyte *, GLsizei, GLsizei, GLsizei);
void                SetupVAOArray( GLuint *, GLuint *, GLuint *, GLfloat *, GLfloat *, GLfloat *, GLubyte *, GLsizei, GLsizei, GLsizei, GLsizei);

#endif
