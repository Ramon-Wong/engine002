#include "functions.h"



void Init(void){
    const int window_width	= 800;
    const int window_height = 600;
 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  	GLFWwindow * window = glfwCreateWindow( window_width, window_height, "LearnOpenGL", NULL, NULL);
	if( !window){
		Shutdown(1);
	}

 	glfwMakeContextCurrent(window);
 
	printf("GL VENDOR:--- %s \n", glGetString(GL_VENDOR));
	printf("GL RENDERER:- %s \n", glGetString(GL_RENDERER));
	printf("GL VERSION:-- %s \n", glGetString(GL_VERSION));
	printf("GL SHADING:-- %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));


	while(1){ 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		
		glfwSwapBuffers(window);
	}
 }


void Shutdown(int return_code){

	glfwTerminate();
	exit(return_code);
}
