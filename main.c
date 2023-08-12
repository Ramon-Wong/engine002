#include "functions.h"



int main(int arg, char * argv[]){

  if(!glfwInit()) {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  } 

  GLFWwindow * window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);

  if(!window) {
    fprintf(stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);
                                  
  glewExperimental = GL_TRUE;
  glewInit();

  const GLubyte* renderer   = glGetString(GL_RENDERER);
  const GLubyte* version    = glGetString(GL_VERSION);
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  printf("Rendering");


  main_loop(window);
  

  printf("end of this 'loop'");
  glfwTerminate();

  return 0;
}