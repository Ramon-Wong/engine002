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

#define RIGHT   0
#define LEFT    1
#define BOTTOM  2
#define TOP     3
#define BACK    4    
#define FRONT   5


extern GLFWwindow * wnd;

extern GLfloat      box_vertices[72];
extern GLfloat      box_normals[72];
extern GLfloat      box_colors[72];
extern GLfloat      box_texcoords[48];
extern GLubyte      box_indices[36];

void				Init(void);
void				Shut_Down(int);
void				Main_Loop(void);

void				ShaderSetup1(void);

GLuint				ReadGLSLScript(GLuint, uint, const char *);
void				LinkPrograms(GLuint);

void                CreateTexture( GLenum, GLuint *, unsigned char *, int, int, GLenum);
GLuint              LoadTexture( GLuint, const char *, const char *, int);

void                setPlanes( float *);
int                 PointinFrustum(float *);
//                  use this with Pose and View as parameters and speed
void                MoveCamera(float *, float *, float);           
void                RotateCamera(float *, float *, float, float, float, float);
void                StrafeCamera(float *, float *, float);

void				Draw_Object(GLuint, int);

void                gMatrixRotation( GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
void                gMatrixTranslation( GLuint, GLfloat, GLfloat, GLfloat);
void                gPopMatrix(GLuint, const char *);

void                SetupVAO( GLuint *, GLuint *, GLuint *, GLfloat *, GLfloat *, GLubyte *, GLsizei, GLsizei, GLsizei);
void                SetupVAOArray( GLuint *, GLuint *, GLuint *, GLfloat *, GLfloat *, GLfloat *, GLubyte *, GLsizei, GLsizei, GLsizei, GLsizei);

#endif
