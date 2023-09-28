#include "functions.h"




//~ gcc -Wall -o "%e" "%f" functions.c utils.c ShaderUtils.c Matrix4x.c -lm -lglfw -lGL -lGLEW  

// http://www.songho.ca/opengl/gl_vbo.html#example1

// gcc -Wall -c "%f" functions.c utils.c ShaderUtils.c Matrix4x.c
// gcc -Wall -o "%e" "%f" functions.c utils.c ShaderUtils.c Matrix4x.c -lGLEW -lglfw -lGL -lGLU -lm

// 



 
  
int main(void){
 
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow * window = glfwCreateWindow( Screen_width, Screen_height, "Hello GLFW", NULL, NULL);
  if (!window) {
       glfwTerminate();
  }
	
 	glfwMakeContextCurrent(window);		
      
	printf("GL VENDOR:--- %s \n", glGetString(GL_VENDOR));
	printf("GL RENDERER:- %s \n", glGetString(GL_RENDERER));
	printf("GL VERSION:-- %s \n", glGetString(GL_VERSION));
	printf("GL SHADING:-- %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));

  // Here is where the magic happens
  //
  Mainloop();
  //
  // End

  Shutdown();
	
  return 0;
}
