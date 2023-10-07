#include "functions.h"
 

//~ gcc -Wall -o "%e" "%f" functions.c utils.c ShaderUtils.c Matrix4x.c -lm -lglfw -lGL -lGLEW  


// gcc -Wall -c "%f" functions.c utils.c ShaderUtils.c Matrix4x.c
// gcc -Wall -o "%e" "%f" functions.c utils.c ShaderUtils.c Matrix4x.c -lGLEW -lglfw -lGL -lGLU -lm

  
int main(void){

  if( glfwInit() != GL_TRUE){     Shutdown(1);}
	
	GLFWwindow * wnd = glfwCreateWindow( 800, 600, "Hello Triangle", NULL, NULL);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if(!wnd) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
	}

	glfwMakeContextCurrent(wnd);
 
   // Initialize GLEW
    GLenum glewInitResult = glewInit();
    if (glewInitResult != GLEW_OK) {
        fprintf(stderr, "Error initializing GLEW: %s\n", glewGetErrorString(glewInitResult));
        glfwTerminate();
        Shutdown(1);
    }

	printf("GL VENDOR:--- %s \n", glGetString(GL_VENDOR));
	printf("GL RENDERER:- %s \n", glGetString(GL_RENDERER));
	printf("GL VERSION:-- %s \n", glGetString(GL_VERSION));
	printf("GL SHADING:-- %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	Main_Loop();
	Shutdown(0);
  
	return 0;
}