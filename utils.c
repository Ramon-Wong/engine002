#include "functions.h"


void Init(void){
    const int window_width = 800;
    const int window_height = 600;
 
    if( glfwInit() != GL_TRUE)
    Shut_Down(1);
  
    if( glfwOpenWindow( window_width, window_height, 5, 6, 5, 0, 0, 0, GLFW_WINDOW) != GL_TRUE)
		    Shut_Down(1);
		
    glfwSetWindowTitle("The GLFW Window");
 
	  printf("GL VENDOR:--- %s \n", glGetString(GL_VENDOR));
	  printf("GL RENDERER:- %s \n", glGetString(GL_RENDERER));
	  printf("GL VERSION:-- %s \n", glGetString(GL_VERSION));
	  printf("GL SHADING:-- %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
 
 }


void Shut_Down(int return_code){
    glDeleteProgram( GLSL_Program);
	  glDeleteShader( GLSL_vertex);
	  glDeleteShader( GLSL_fragment);		
	
	  glfwTerminate();
	  exit(return_code);
}
