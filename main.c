#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


	GLfloat vertices[] = {	-1.0,  1.0, 0.0,		// 0
							-1.0, -1.0, 0.0,		// 1
							 1.0, -1.0, 0.0,		// 2
							 1.0,  1.0, 0.0};		// 3

	GLubyte indices[] = { 0, 1, 2, 0, 2, 3};

	GLfloat texCoords[] = { 0.0, 1.0,   			// Vertex 0
                        	0.0, 0.0,   			// Vertex 1
                        	1.0, 0.0,   			// Vertex 2
                        	1.0, 1.0 }; 			// Vertex 3



void SizeOpenGLScreen( int, int);




int main(void){
	GLFWwindow			*	window;
	const GLubyte		*	renderer;
	const GLubyte		*	version;


	if (!glfwInit())
    	exit(EXIT_FAILURE);
  		window = glfwCreateWindow( 800, 600, "Chapter 1: Simple GLFW Example", NULL, NULL);

	if (!window){
    	glfwTerminate();
    	exit(EXIT_FAILURE);
  	}

    glfwMakeContextCurrent(window);

	renderer	= glGetString(GL_RENDERER);
	version		= glGetString(GL_VERSION);
	
	printf("\n Renderer: %s", renderer);
	printf("\n OpenGL version supported %s", version);
	printf("\n GL VENDOR:---  %s ",	glGetString(GL_VENDOR));
	printf("\n GL VERSION:--  %s ", glGetString(GL_VERSION));
	printf("\n GL SHADING:--  %s ",	glGetString(GL_SHADING_LANGUAGE_VERSION));

    // float ratio;
    int width, height;

    glfwGetFramebufferSize( window, &width, &height);
    // ratio = (float) width / (float) height;

	glEnable( GL_DEPTH_TEST);
	glDepthFunc( GL_LESS);

    SizeOpenGLScreen( width, height);

	while (!glfwWindowShouldClose(window)){

		if(glfwGetKey( window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
			glfwSetWindowShouldClose( window, 1);
		}

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
		gluLookAt( 0, 0, 6, 0, 0, 0, 0, 1, 0);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glfwPollEvents();
		glfwSwapBuffers(window);

	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}


void SizeOpenGLScreen(int width, int height){
	if(height==0){
		height=1;
	}

	glViewport( 0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 45.0f, (GLfloat)width/(GLfloat)height, .5f ,150.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
