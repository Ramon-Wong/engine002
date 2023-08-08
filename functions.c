#include "functions.h"


void Main_Loop(GLFWwindow * window){
	
	while(1){ 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		
		glfwSwapBuffers(window);
	}
}