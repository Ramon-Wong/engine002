#include "functions.h"



#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

	GLfloat vertices[] = {	-1.0,  1.0, 0.0,		// 0
							-1.0, -1.0, 0.0,		// 1
							 1.0, -1.0, 0.0,		// 2
							 1.0,  1.0, 0.0};		// 3


	GLfloat texCoords[] = { 0.0, 1.0,   			// Vertex 0
                        	0.0, 0.0,   			// Vertex 1
                        	1.0, 0.0,   			// Vertex 2
                        	1.0, 1.0 }; 			// Vertex 3

	GLubyte indices[] = { 0, 1, 2, 0, 2, 3};


void SizeOpenGLScreen( int, int);


int main(void){

  	GLFWwindow 			*	window;
	const GLubyte		*	renderer;
	const GLubyte		*	version;
	GLuint 					m_texture;

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

		gloadTexture( &m_texture, data, x, y, n);	

		if(n == 3) 
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB,		GL_UNSIGNED_BYTE, data);
		else if (n == 4) 
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGBA,	GL_UNSIGNED_BYTE, data);

		printf("\n texture Process %i/%i/%i \n", x, y, n);
    }

	stbi_image_free(data);    

  	while (!glfwWindowShouldClose(window)){

		if(glfwGetKey( window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
			glfwSetWindowShouldClose( window, 1);
		}

		// glClear(GL_COLOR_BUFFER_BIT); 
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
		gluLookAt( 0, 0, 6, 0, 0, 0, 0, 1, 0);

		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, m_texture);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);

		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		glBindTexture(GL_TEXTURE_2D, 0);

		glfwPollEvents();
    	glFlush();
		glfwSwapBuffers(window);

  }

	glDeleteTextures(1, &m_texture);	

  	glfwDestroyWindow(window);
  	glfwTerminate();
  	exit(EXIT_SUCCESS);
}





// https://github.com/Martinfx/LearnOpenGL/blob/master/planeWithTexture/main.cpp