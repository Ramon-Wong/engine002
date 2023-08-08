#include "functions.h"


void Init(void){
    const int window_width = 800;
    const int window_height = 600;
 
    if( glfwInit() != GL_TRUE)
    Shutdown(1);
  
  	GLFWwindow * window = glfwCreateWindow( window_width, window_height, "LearnOpenGL", NULL, NULL);
	if( !window ){
		Shutdown(1);
	}
		
 
	  printf("GL VENDOR:--- %s \n", glGetString(GL_VENDOR));
	  printf("GL RENDERER:- %s \n", glGetString(GL_RENDERER));
	  printf("GL VERSION:-- %s \n", glGetString(GL_VERSION));
	  printf("GL SHADING:-- %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
 
 }


void Shutdown(int return_code){
/	
	glfwTerminate();
	exit(return_code);
}
