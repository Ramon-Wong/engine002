#include "functions.h"

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

void	glTexture( GLuint *, unsigned char *, int, int, int);



















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

 		glTexture( &m_texture, data, x, y, n);

		printf("\n\n Texture Process %i/%i/%i \n\n", x, y, n);
    }

	stbi_image_free(data);    

	generateShadowFBO();
	loadShadowShader();
	
	// This is important, if not here, FBO's depthbuffer won't be populated.
	glEnable(GL_DEPTH_TEST);
	glClearColor(0,0,0,1.0f);
	
	glEnable(GL_CULL_FACE);
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);


  	while (!glfwWindowShouldClose(window)){

		if(glfwGetKey( window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
			glfwSetWindowShouldClose( window, 1);
		}

		// glClear(GL_COLOR_BUFFER_BIT); 
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();

		renderScene(window);		// Renderscene
		// gluLookAt( 0, 0, 6, 0, 0, 0, 0, 1, 0);

		// glBegin (GL_QUADS);
		// 	glVertex3f(-1.0,  1.0, 0.0);
		// 	glVertex3f(-1.0, -1.0, 0.0);		// 1
		// 	glVertex3f( 1.0, -1.0, 0.0);		// 2
		// 	glVertex3f( 1.0,  1.0, 0.0);		// 3
		// glEnd();

		glfwPollEvents();
    	// glFlush();
		glfwSwapBuffers(window);

  }

	Release();
	glDeleteTextures(1, &m_texture);	

  	glfwDestroyWindow(window);
  	glfwTerminate();
  	exit(EXIT_SUCCESS);
}


void glTexture( GLuint * texture, unsigned char * data, int x, int y, int b){

	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if(b == 3) 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB,		GL_UNSIGNED_BYTE, data);
	else if (b == 4) 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGBA,	GL_UNSIGNED_BYTE, data);

}





// https://github.com/Martinfx/LearnOpenGL/blob/master/planeWithTexture/main.cpp