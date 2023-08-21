#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>



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


int main(void){

    GLFWwindow      * window;
	  const GLubyte		*	renderer;
	  const GLubyte		*	version;

    GLfloat vertices[] = {	 -1.0,  1.0, 0.0,		// 0
							               -1.0, -1.0, 0.0,		// 1
							                1.0, -1.0, 0.0,		// 2
							                1.0,  1.0, 0.0};		// 3

	  GLubyte indices[] = { 0, 1, 2, 0, 2, 3};

    // float ratio;
    int width   = 800;
    int height  = 600;

    glfwInit();
    window = glfwCreateWindow( width, height, "Simple GLFW Example", NULL, NULL);

    if (!window){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
	  glewExperimental = GL_TRUE;
	  // glewInit();
 
	  renderer	= glGetString(GL_RENDERER);
	  version		= glGetString(GL_VERSION);
	
	  printf("\n Renderer: %s", renderer);
	  printf("\n OpenGL version supported %s", version);
	  printf("\n GL VENDOR:---  %s ",	glGetString(GL_VENDOR));
	  printf("\n GL VERSION:--  %s ",  	glGetString(GL_VERSION));
	  printf("\n GL SHADING:--  %s ",	glGetString(GL_SHADING_LANGUAGE_VERSION));

	  glEnable( GL_DEPTH_TEST);
	  glDepthFunc( GL_LESS);



    glfwGetFramebufferSize(window, &width, &height);
    // ratio = (float) width / (float) height;

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

		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);

		glDisableClientState(GL_VERTEX_ARRAY);

		glfwPollEvents();
		glfwSwapBuffers(window);


  }
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}



