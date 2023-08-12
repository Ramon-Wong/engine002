#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>




GLfloat vertices[]	= {  0.5f, 0.5f, 0.0f, 
            						-0.5f, 0.5f, 0.0f,
            						-0.5f,-0.5f, 0.0f, 
						             0.5f,-0.5f, 0.0f};	

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

    float ratio;
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    ratio = (float) width / (float) height;



  while (!glfwWindowShouldClose(window)){


    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

    Draw_Square();

    // glBegin(GL_TRIANGLES);
    // glColor3f(1.f, 0.f, 0.f);
    // glVertex3f(-0.6f, -0.4f, 0.f);
    // glColor3f(0.f, 1.f, 0.f);
    // glVertex3f(0.6f, -0.4f, 0.f);
    // glColor3f(0.f, 0.f, 1.f);
    // glVertex3f(0.f, 0.6f, 0.f);
    // glEnd();
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