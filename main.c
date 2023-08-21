#include "functions.h"






int main(int arg, char * argv[]) {

	GLFWwindow			*	window = NULL;
	const GLubyte		*	renderer;
	const GLubyte		*	version;

	if(!glfwInit()){
		fprintf( stderr,"ERROR: could not start GLFW3\n");
		return 1;
	}

	window = glfwCreateWindow( 800, 600, "Hello Triangle", NULL, NULL);
	if(!window){
		fprintf( stderr,"ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent( window );
	glewExperimental = GL_TRUE;
	glewInit();
 
	renderer	= glGetString(GL_RENDERER);
	version		= glGetString(GL_VERSION);
	
	printf("\n Renderer: %s", renderer);
	printf("\n OpenGL version supported %s", version);
	printf("\n GL VENDOR:---  %s ",	glGetString(GL_VENDOR));
	printf("\n GL VERSION:--  %s ",  	glGetString(GL_VERSION));
	printf("\n GL SHADING:--  %s ",	glGetString(GL_SHADING_LANGUAGE_VERSION));


	printf("Arg Total: %i\n", arg);
	if(arg > 0){
		int e;
		for( e = 0; e < arg; e++){
			printf("\nArg %i: %s", e, argv[e]);
		}
	}
	printf("\n");

	glEnable( GL_DEPTH_TEST);
	glDepthFunc( GL_LESS);

	Mainloop(arg, argv, window);

	glfwTerminate();
	return 0;
}