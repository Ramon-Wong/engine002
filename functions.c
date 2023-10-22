#include "functions.h"

GLFWwindow * wnd;


void Shut_Down(int i){

	return i;
}


void Main_Loop(void){

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL error: %d\n", error);
		Shut_Down(1);
    }


	while(!glfwWindowShouldClose(wnd)){


		if(glfwGetKey( wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS){
			glfwSetWindowShouldClose( wnd, 1);
		}

		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			fprintf(stderr, "OpenGL error in mainloop: %d\n", error);
			Shut_Down(1);
		}
		glfwSwapBuffers(wnd);
		glfwPollEvents();
	}
}
