#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h> 
#include <math.h>

#include "/serious project/wren/src/include/wren.h"
#include "matrix.h"
#include "objects.h"
#include "utils.h"


#define RIGHT       0
#define LEFT        1
#define BOTTOM      2
#define TOP         3
#define BACK        4
#define FRONT       5


extern GLfloat      box_vertices[72];
extern GLfloat      box_normals[72];
extern GLfloat      box_colors[72];
extern GLfloat      box_texcoords[48];
extern GLubyte      box_indices[36];

extern GLfloat      grid_lines[36];
extern GLubyte      grid_indices[4];

void				Shutdown(int);
void				Main_Loop(void);
void				Draw_Square(void);
void				Draw(void);

char *				ReadFile(const char *);

void				ShaderSetup();
GLuint              ReadGLSLScript(GLuint, unsigned int, const char *);
void	            LinkPrograms(GLuint);

void                generalBufferObject( unsigned int, int, void *, const char *, GLenum);

void                SetupVAOSingle( GLuint *, GLuint *, GLuint *, GLfloat *, GLubyte *, GLsizei, GLsizei);
void                SetupVAO( GLuint *, GLuint *, GLuint *, GLfloat *, GLfloat *, GLubyte *, GLsizei, GLsizei, GLsizei);
void                SetupVAOArray( GLuint *, GLuint *, GLuint *, GLfloat *, GLfloat *, GLfloat *, GLubyte *, GLsizei, GLsizei, GLsizei, GLsizei);

void                setPlanes( float * ProjView);
int                 PointinPlane( int, float *);

// void                gMatrixRotation( GLfloat, GLfloat, GLfloat, GLfloat);
// void                gMatrixTranslation( GLfloat, GLfloat, GLfloat);
// void                gPopMatrix(GLuint Prog, const char * uniform);
void                Draw_Geometry( GLenum, GLuint, int size);



void                Rectangle_Init( RECTANGLE *, float, float, float, float);


void                GLSLProg_Init( GLSL_PROGRAM *);
void                Projection_Init( PROJECTION *);

#endif
