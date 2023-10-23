#include "functions.h"



CAMERA				Camera;
GLSL_PROGRAM		Prog01;			// Landscape

GLfloat vertices[]	= {  1.1f, 1.1f, 0.0f,	-1.1f, 1.1f, 0.0f,	-1.1f,-1.1f, 0.0f,	1.1f,-1.1f, 0.0f};


void CheckGLError(){
	GLenum error = glGetError();
	while(error != GL_NO_ERROR) {
		fprintf(stderr, "OpenGL error: %d\n", error);
			// Shutdown();
	}
}


void Shutdown(int return_code){
	Prog01.Release( &Prog01);

	glfwTerminate();
	exit(return_code);
}


void Main_Loop(void){

	// ShaderSetup();
	glEnable(GL_DEPTH_TEST);

	GLFWwindow * wnd = glfwGetCurrentContext();

	GLSLProg_Init(&Prog01);
	Camera_Init(&Camera);

	// double old_time = glfwGetTime();
	
	float Pose[] = {  0.0f,  0.0f,  6.0f};
	float View[] = {  0.0f,  0.0f, 12.0f}; 
	float Upvx[] = {  0.0f,  1.0f,  0.0f};
	
	float aspect_ratio = ((float)600) / 800;

	Camera.SetProjection( &Camera, 0.5f, -0.5f, -0.5f * aspect_ratio, 0.5f * aspect_ratio, 1.0f, 100.0f);	// NEW SHIT
	Camera.SetCamera( &Camera, Pose, View, Upvx);
	Prog01.Init( &Prog01, "GLSL/VShader.glsl", "GLSL/FShader.glsl");

	while(!glfwWindowShouldClose(wnd)){

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if(glfwGetKey( wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS){	glfwSetWindowShouldClose( wnd, 1);}
		// Prog01.EnableProgram(&Prog01);



		glfwSwapBuffers(wnd);
		glfwPollEvents();
		CheckGLError();
	}
	// clean stuff that is out of the loop.

	Prog01.Release( &Prog01);
}
