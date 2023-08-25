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


	GLfloat texCoords[] = { 0.0, 1.0,   			// Vertex 0
                        	0.0, 0.0,   			// Vertex 1
                        	1.0, 0.0,   			// Vertex 2
                        	1.0, 1.0 }; 			// Vertex 3

	GLubyte indices[] = { 0, 1, 2, 0, 2, 3};


// GLfloat vertices[]	= {  0.5f, 0.5f, 12.0f, 
//             						-0.5f, 0.5f, 12.0f,
//             						-0.5f,-0.5f, 12.0f, 
// 						             0.5f,-0.5f, 12.0f};	

// GLubyte indices[]	= {  0, 1, 2, 2, 3, 0}; 

void SizeOpenGLScreen( int, int);




int main(void){

  	GLFWwindow 			*	window;
	const GLubyte		*	renderer;
	const GLubyte		*	version;
	// GLuint 					m_texture;

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

    glfwGetFramebufferSize(window, &width, &height);
    // ratio = (float) width / (float) height;

	glEnable( GL_DEPTH_TEST);
	glDepthFunc( GL_LESS);

    SizeOpenGLScreen( width, height);

    int x,y,n;
    unsigned char * data = stbi_load("skin2.tga", &x, &y, &n, 0);
    if (data == NULL) {
		printf("\nCan't open tga file");
    } else {

		// glGenTextures(1, &m_texture);
		// glBindTexture(GL_TEXTURE_2D, m_texture);

		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data); 
 		// // glGenerateMipmap(GL_TEXTURE_2D);
		// glBindTexture(GL_TEXTURE_2D, 0);

		printf("\n texture Process %i/%i/%i \n", x, y, n);
    }
    

  	while (!glfwWindowShouldClose(window)){

		if(glfwGetKey( window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
			glfwSetWindowShouldClose( window, 1);
		}

		glClear(GL_COLOR_BUFFER_BIT); 
		// glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
		gluLookAt( 0, 0, 6, 0, 0, 0, 0, 1, 0);


		// glBindTexture(GL_TEXTURE_2D, m_texture);

		// glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		// glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);

		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		// glBindTexture(GL_TEXTURE_2D, 0);


		glfwPollEvents();
		glfwSwapBuffers(window);


  }

	// stbi_image_free(data);
	// glDeleteTextures(1, &m_texture);	

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
