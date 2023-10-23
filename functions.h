#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h> 
#include <GL/glu.h> 
#include <math.h>

#include "matrix.h"
#include "objects.h"
#include "utils.h"


extern GLfloat      box_vertices[72];
extern GLfloat      box_normals[72];
extern GLfloat      box_colors[72];
extern GLfloat      box_texcoords[48];
extern GLubyte      box_indices[36];

extern GLfloat      grid_lines[36];
extern GLubyte      grid_indices[4];

void				Shutdown(int);
void				Main_Loop(void);

void				ShaderSetup();
GLuint              ReadGLSLScript(GLuint, unsigned int, const char *);
void	            LinkPrograms(GLuint);

void                SetupVAOSingle( GLuint *, GLuint *, GLuint *, GLfloat *, GLubyte *, GLsizei, GLsizei);
void                SetupVAO( GLuint *, GLuint *, GLuint *, GLfloat *, GLfloat *, GLubyte *, GLsizei, GLsizei, GLsizei);
void                SetupVAOArray( GLuint *, GLuint *, GLuint *, GLfloat *, GLfloat *, GLfloat *, GLubyte *, GLsizei, GLsizei, GLsizei, GLsizei);

void                createDepthMapFBO(GLuint *, int, int, GLuint *);

void                setPlanes( float * ProjView);
int                 PointinPlane( int, float *);

void                Camera_Init(CAMERA *);
void                GLSLProg_Init(GLSL_PROGRAM *);
void                Rectangle_Init( RECTANGLE *, float, float, float, float);



#endif
