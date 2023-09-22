#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <assert.h>
#include <string.h>
#include <math.h>

#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

extern GLFWwindow * window;


int                 Init();
void				Main_Loop();
int                 Shutdown();


#endif