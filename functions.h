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

#define RIGHT   0
#define LEFT    1
#define BOTTOM  2
#define TOP     3
#define BACK    4
#define FRONT   5

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

// void                gMatrixRotation( GLfloat, GLfloat, GLfloat, GLfloat);
// void                gMatrixTranslation( GLfloat, GLfloat, GLfloat);
// void                gPopMatrix(GLuint Prog, const char * uniform);
void                Draw_Geometry( GLenum, GLuint, int size);




typedef struct{
    GLubyte         indices[6];
    float           width;
    float           height;
    float           vertices[12];
    float           TexCoords[8];

    void          (*Render)(void *, float, float);
}RECTANGLE;

void                Rectangle_Init( RECTANGLE *, float, float, float, float);


typedef struct{
    GLuint          GLSL_Prog[3];
    float           TransRotMatrix[16]; 
    int             Counter;
    GLuint          gTexture;

    void          (*Init)( void *, const char *, const char *);
    void          (*EnableProgram)( void *);
    void          (*DisableProgram)( void *);
    void          (*Release)(void *);

    GLuint        (*GetProgram)( void *);  
    void          (*SetUniform3f)( void *, const char *, float, float, float);
    void          (*SetUniform1f)( void *, const char *, float);
    void          (*SetUniform1i)( void *, const char *, int);

    void          (*gMatrixRotation)( void *, float, float, float, float);
    void          (*gMatrixTranslation)( void *, float, float, float);
    void          (*gPopMatrix)( void *, const char *);

    void          (*LoadTexture)( void *, const char *, const char *, int);
    void          (*EnableTexture)(void *, GLenum);
    void          (*DisableTexture)(void *);

    GLuint          bufferID;
    void          (*ShaderBufferObject)(void *, int, float *, const char *);

}GLSL_PROGRAM;


#define RIGHT   0
#define LEFT    1
#define BOTTOM  2
#define TOP     3
#define BACK    4
#define FRONT   5

typedef struct{
    float           Cam[3][3];                      // Camera Pose/View/Upvx
    float           MouseCoord[2];                  // Mouse Coords
    GLfloat         Proj_Matrix[16];                // frustum matrix
    GLfloat         View_Matrix[16];                // Camera matrix
    GLfloat         Temp_Matrix[16];                // Temp Camera matrix
    GLfloat         Orth_Matrix[16];                // Ortho 2D view
    GLfloat         Proj_View[16];                  // Projection * Camera VIew
    GLfloat         Orth_View[16];                  // Ortho * Camera VIew
    float           gFrustum[6][4];                 // Frustum plane

    void          (*SetProjection)( void *, float, float, float, float, float, float);
    void          (*SetOrthoGraphic)( void *, float, float, float, float, float, float);
    void          (*SetCamera)( void *, float *, float *, float *); 
    void          (*Lookup)( void *);
    void          (*uProjView)( void *, GLuint, const char *);
    void          (*oProjView)( void *, GLuint, const char *);

    void          (*MouseCamera)( void *, float, float);
    void          (*MoveCamera)( void *, float);
    void          (*RotateCamera)( void *, float, float, float, float);
    void          (*StrafeCamera)( void *, float);
    int           (*PointinPlane)( void *, int, float *);

    // todo Frustum Culling!!
}CAMERA;

void                Camera_Init(CAMERA *);
void                GLSLProg_Init(GLSL_PROGRAM *);

#endif
