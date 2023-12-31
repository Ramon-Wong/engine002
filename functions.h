#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h> 
#include <math.h>
#include "objects.h"


void				Shutdown(int);
void				Main_Loop(void);

void				ShaderSetup();
GLuint              ReadGLSLScript(GLuint, unsigned int, const char *);
void	            LinkPrograms(GLuint);

void                Camera_Init(CAMERA *);
void                GLSLProg_Init(GLSL_PROGRAM *);

#endif
