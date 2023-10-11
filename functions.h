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

#define             RIGHT       0
#define             LEFT        1
#define             BOTTOM      2
#define             TOP         3
#define             BACK        4
#define             FRONT       5

#define             MAX_SHADER  5

extern GLfloat      box_vertices[72];
extern GLfloat      box_normals[72];
extern GLfloat      box_colors[72];
extern GLfloat      box_texcoords[48];
extern GLubyte      box_indices[36];

extern GLfloat      grid_lines[36];
extern GLubyte      grid_indices[4];

void				Init(void);
void				Shutdown(int);
void				Main_Loop(void);
void				Draw_Square(void);
void				Draw(void);

char *				ReadFile(const char *);

void				ShaderSetup();
GLuint              ReadGLSLScript(GLuint, unsigned int, const char *);
void	            LinkPrograms(GLuint);

void                SetupVAOSingle( GLuint *, GLuint *, GLuint *, GLfloat *, GLubyte *, GLsizei, GLsizei);
void                SetupVAO( GLuint *, GLuint *, GLuint *, GLfloat *, GLfloat *, GLubyte *, GLsizei, GLsizei, GLsizei);
void                SetupVAOArray( GLuint *, GLuint *, GLuint *, GLfloat *, GLfloat *, GLfloat *, GLubyte *, GLsizei, GLsizei, GLsizei, GLsizei);

void                setPlanes( float * ProjView);
int                 PointinPlane( int, float *);

void                Draw_Geometry( GLenum, GLuint, int size);



void                Camera_Init(CAMERA *);
void                GLSLProg_Init(GLSL_PROGRAM *);
void                Rectangle_Init( RECTANGLE *, float, float, float, float);


#define SUBSTRACT_VECTOR(result, Vec1, Vec2) do { \
    result[0] = Vec2[0] - Vec1[0]; \
    result[1] = Vec2[1] - Vec1[1]; \
    result[2] = Vec2[2] - Vec1[2]; \
} while(0)

#define ADD_VECTOR(result, Vec1, Vec2) do { \
    result[0] = Vec2[0] + Vec1[0]; \
    result[1] = Vec2[1] + Vec1[1]; \
    result[2] = Vec2[2] + Vec1[2]; \
} while(0)

#endif
