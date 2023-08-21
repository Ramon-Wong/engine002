#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>




GLfloat vertices[]	= {  0.5f, 0.5f, 12.0f, 
            						-0.5f, 0.5f, 12.0f,
            						-0.5f,-0.5f, 12.0f, 
						             0.5f,-0.5f, 12.0f};	

GLubyte indices[]	= {  0, 1, 2, 2, 3, 0}; 


void Draw_Square();

int main(void){
  GLFWwindow * window;

  if (!glfwInit())
    exit(EXIT_FAILURE);
  window = glfwCreateWindow( 800, 600, "Chapter 1: Simple GLFW Example", NULL, NULL);

  if (!window){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);

    // float ratio;
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    // ratio = (float) width / (float) height;

    glViewport(0, 0, width, height);

  while (!glfwWindowShouldClose(window)){

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	// float View[] = {  0.0f,  0.0f, 12.0f};
	// float Pose[] = {  0.0f,  0.0f,  6.0f};
	// float Upvx[] = {  0.0f,  1.0f,  0.0f};

  // void gluLookAt(	GLdouble eyeX,    GLdouble eyeY,    GLdouble eyeZ,
 	//                 GLdouble centerX, GLdouble centerY, GLdouble centerZ,
  //                 GLdouble upX,     GLdouble upY,     GLdouble upZ);
    gluLookAt( 0.0, 0.0, 6.0, 0.0, 0.0, 12.0, 0.0, 1.0, 0.0);
    // glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

    Draw_Square();

    glfwSwapBuffers(window);
    glfwPollEvents();
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