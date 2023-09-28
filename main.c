#include "functions.h"




//~ gcc -Wall -o "%e" "%f" functions.c utils.c ShaderUtils.c Matrix4x.c -lm -lglfw -lGL -lGLEW  

// http://www.songho.ca/opengl/gl_vbo.html#example1

// gcc -Wall -c "%f" functions.c utils.c ShaderUtils.c Matrix4x.c
// gcc -Wall -o "%e" "%f" functions.c utils.c ShaderUtils.c Matrix4x.c -lGLEW -lglfw -lGL -lGLU -lm


// 
// "GLSL/FShader.glsl"


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
	  glViewport( 0, 0, window_width, window_height);


	  while(!glfwWindowShouldClose(window)) {
		  // wipe the drawing surface clear
		  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {  Shutdown(0);}





		  glfwPollEvents();
		  glfwSwapBuffers(window);
	  }	
  }





// #include "functions.h"
 
  
int main(void){

  Init();
  Shutdown(0);
  
  return 0;
}
