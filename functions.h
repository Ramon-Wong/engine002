#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "matrix.h"

// Resolution mode  800 x 600  
// Resolution mode 1280 x 800  
// Resolution mode 1600 x 900  
// Resolution mode 1920 x 1080 

#define Screen_width    800
#define Screen_height   600


//      Shaderutils.c 
void	            ShaderSetup1();
GLuint				ReadGLSLScript(GLuint, uint, const char *);
void				LinkPrograms(GLuint);

void                Mainloop(void);
void                Shutdown(void);

void                SetupVAO( GLuint *, GLuint *, GLuint *, GLfloat *, GLfloat *, GLubyte *, GLsizei, GLsizei, GLsizei);
void                SetupVAOArray( GLuint *, GLuint *, GLuint *, GLfloat *, GLfloat *, GLfloat *, GLubyte *, GLsizei, GLsizei, GLsizei, GLsizei);

#endif