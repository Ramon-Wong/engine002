#include "functions.h"


unsigned int		GLSL_Program;
unsigned int		GLSL_vertex;
unsigned int		GLSL_fragment;

GLfloat				Proj_Matrix[16];
GLfloat				View_Matrix[16];


float points[] = {
	0.0f,  0.5f,  0.0f,
	0.5f, -0.5f,  0.0f,
   -0.5f, -0.5f,  0.0f
};


void Init(void){
	const int window_width  = 800;
    const int window_height = 600;
 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow * window = glfwCreateWindow( window_width, window_height, "Hello GLFW", NULL, NULL);
    if (!window) {
        Shutdown(1);
    }
	
 	glfwMakeContextCurrent(window);		
      
	printf("GL VENDOR:--- %s \n", glGetString(GL_VENDOR));
	printf("GL RENDERER:- %s \n", glGetString(GL_RENDERER));
	printf("GL VERSION:-- %s \n", glGetString(GL_VERSION));
	printf("GL SHADING:-- %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
 
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

	ShaderSetup("vshader.glsl", "fshader.glsl", &GLSL_Program, GLSL_vertex, GLSL_fragment);


	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), &points, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);



	while(!glfwWindowShouldClose(window)) {
  	// wipe the drawing surface clear
  	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    	Shutdown(0);
    }

  	glUseProgram(GLSL_Program);
  	glBindVertexArray(vao);
  	glDrawArrays(GL_TRIANGLES, 0, 3);

	glfwPollEvents();
  	glfwSwapBuffers(window);
	}	
 }


 void Shutdown(int return_code){
    
	glfwTerminate();
	exit(return_code);
}
