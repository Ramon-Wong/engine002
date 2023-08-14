#include "functions.h"



void Init(void){
 
	if( glfwInit() != GL_TRUE)
	Shut_Down(1);
  
	wnd = glfwCreateWindow( 800, 600, "Hello Triangle", NULL, NULL);

	if(!wnd) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
	
	}

	glfwMakeContextCurrent(wnd);
 
	printf("GL VENDOR:--- %s \n", glGetString(GL_VENDOR));
	printf("GL RENDERER:- %s \n", glGetString(GL_RENDERER));
	printf("GL VERSION:-- %s \n", glGetString(GL_VERSION));
	printf("GL SHADING:-- %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
 
	GLSL_Program		= 0;
	GLSL_fragment		= 0;
	GLSL_vertex			= 0;	

 }

void Shut_Down(int return_code){
		
	if( GLSL_Program){
		glDeleteProgram( GLSL_Program);
		glDeleteShader( GLSL_vertex);
		glDeleteShader( GLSL_fragment);		
	}

	glfwTerminate();
	exit(return_code);
}


