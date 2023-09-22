#include "functions.h"

int Init(){

    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(800, 600, "Legacy OpenGL Square", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }	
    glfwMakeContextCurrent(window);
	
	return -1;
}

int Shutdown(){
	glfwTerminate();
	return -1;
}