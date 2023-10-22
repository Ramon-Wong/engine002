#include "functions.h"




void CheckGLError(){
	GLenum error = glGetError();
	while(error != GL_NO_ERROR) {
		fprintf(stderr, "OpenGL error: %d\n", error);
			// Shutdown();
	}
}


void Shutdown(int return_code){
	
	glfwTerminate();
	exit(return_code);
}


void Main_Loop(void){

	// ShaderSetup();
	glEnable(GL_DEPTH_TEST);

	GLFWwindow * wnd = glfwGetCurrentContext();

	// double old_time = glfwGetTime();
	
	while(!glfwWindowShouldClose(wnd)){


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if(glfwGetKey( wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS){	glfwSetWindowShouldClose( wnd, 1);}




		glfwSwapBuffers(wnd);
		glfwPollEvents();
		CheckGLError();
	}
	// clean stuff that is out of the loop.



}
