#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h> 
#include <math.h>

#include "matrix.h"

#define RIGHT   0
#define LEFT    1
#define BOTTOM  2
#define TOP     3
#define BACK    4
#define FRONT   5


void				Init(void);
void				Shutdown(int);
void				Main_Loop(void);
void				Draw_Square(void);
void				Draw(void);

char *				ReadFile(const char *);

void				ShaderSetup();
GLuint              ReadGLSLScript(GLuint, unsigned int, const char *);
void	            LinkPrograms(GLuint);

void                MoveCamera(float *, float *, float);
void                RotateCamera(float*, float*, float, float, float, float);
void                StrafeCamera(float*, float*, float);

void                SetupVAO( GLuint *, GLuint *, GLuint *, GLfloat *, GLfloat *, GLubyte *, GLsizei, GLsizei, GLsizei);
void                SetupVAOArray( GLuint *, GLuint *, GLuint *, GLfloat *, GLfloat *, GLfloat *, GLubyte *, GLsizei, GLsizei, GLsizei, GLsizei);

void                setPlanes( float * ProjView);

void                gMatrixRotation( GLfloat, GLfloat, GLfloat, GLfloat);
void                gMatrixTranslation( GLfloat, GLfloat, GLfloat);
void                gPopMatrix(GLuint Prog, const char * uniform);
void                Draw_Object( GLuint, int size);


#endif
