#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

	GLfloat vertices[] = {	-1.0,  1.0, 0.0,		// 0
							            -1.0, -1.0, 0.0,		// 1
							             1.0, -1.0, 0.0,		// 2
							             1.0,  1.0, 0.0};		// 3

	GLubyte indices[] = { 0, 1, 2, 0, 2, 3};


// GLfloat vertices[]	= {  0.5f, 0.5f, 12.0f, 
//             						-0.5f, 0.5f, 12.0f,
//             						-0.5f,-0.5f, 12.0f, 
// 						             0.5f,-0.5f, 12.0f};	

// GLubyte indices[]	= {  0, 1, 2, 2, 3, 0}; 

void SizeOpenGLScreen( int, int);
void Draw_Square();



int main(void){
  GLFWwindow * window;

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
	  printf("\n GL VERSION:--  %s ",  	glGetString(GL_VERSION));
	  printf("\n GL SHADING:--  %s ",	glGetString(GL_SHADING_LANGUAGE_VERSION));


    // float ratio;
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    // ratio = (float) width / (float) height;


	  glEnable( GL_DEPTH_TEST);
	  glDepthFunc( GL_LESS);

    glViewport(0, 0, width, height);

  while (!glfwWindowShouldClose(window)){

		if(glfwGetKey( window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
			glfwSetWindowShouldClose( window, 1);
		}

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
		gluLookAt( 0, 0, 6, 0, 0, 0, 0, 1, 0);

    Draw_Square();

		glfwPollEvents();
		glfwSwapBuffers(window);


  }
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}



void Draw_Square(){
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
	
	glDisableClientState(GL_VERTEX_ARRAY); // disable vertex arrays
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
