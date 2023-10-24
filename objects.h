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


#endif