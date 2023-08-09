#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


extern GLfloat		Proj_Matrix[16];
extern GLfloat		View_Matrix[16];

void                Init(void);
void                Shutdown(int);
void                ShaderSetup( const char *, const char * , unsigned int, unsigned int, unsigned int);

#endif