#ifndef _OBJECTS_H
#define _OBJECTS_H

#include "functions.h"


#define UNIFORM_BUFFER_OBJECT  5

typedef struct{
    GLuint          GLSL_Prog[3];
    float           TransRotMatrix[16];
    int             Counter;

    void          (*Init)( void *, const char *, const char *);
    void          (*EnableProgram)( void *);
    void          (*DisableProgram)( void *);
    void          (*Release)(void *);

    GLuint        (*GetProgram)( void *);
    void          (*SetUniformMatrix)( void *, const char *, float *);
    void          (*SetUniform3f)(  void *, const char *, float, float, float);
    void          (*SetUniform1f)(  void *, const char *, float);
    void          (*SetUniform1i)(  void *, const char *, int);

    void          (*gMatrixRotation)( void *, float, float, float, float);
    void          (*gMatrixTranslation)( void *, float, float, float);
    void          (*gPopMatrix)( void *, const char *);

    void          (*LoadTexture)( void *, const char *, const char *, unsigned int *, int);
    void          (*EnableTexture)(void *, unsigned int, GLenum);
    void          (*DisableTexture)(void *);

    GLuint          bufferID[UNIFORM_BUFFER_OBJECT];
    GLuint          UBOcount;                       // set for Uniform Buffer Object count
    void          (*uBufferObject)(void *, int, void *, const char *, GLenum);
    void          (*ObjectUpdate)(void *, int , void *, int, int);

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
    GLfloat         Proj_View[16];                  // Projection * Camera VIew

    float           gFrustum[6][4];                 // Frustum plane

    void          (*SetProjection)( void *, float, float, float, float, float, float);
    void          (*SetOrthoGraphic)( void *, float, float, float, float, float, float);
    void          (*SetCamera)( void *, float *, float *, float *); 
    void          (*Lookup)( void *);


    GLfloat *     (*GetProjView)(void *);

    void          (*MouseCamera)( void *, float, float);
    void          (*MoveCamera)( void *, float);
    void          (*RotateCamera)( void *, float, float, float, float);
    void          (*StrafeCamera)( void *, float);
    int           (*PointinPlane)( void *, int, float *);

    // todo Frustum Culling!!
}CAMERA;


#endif