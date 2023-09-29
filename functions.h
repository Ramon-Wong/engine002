#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h> 
#include <math.h>

#include "matrix.h"


void				Init(void);
void				Shut_Down(int);
void				Main_Loop(void);
void				Draw_Square(void);
void				Draw(void);

char *				ReadFile(const char *);

void				ShaderSetup();
GLuint              ReadGLSLScript(GLuint, uint, const char *);
void	            LinkPrograms(GLuint);

#endif
