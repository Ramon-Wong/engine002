#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>



int main(int arg, char * argv[]){

    if(!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    } 
    printf("\n\n\tHello GLFW3/GLEW with OpenGL 4.0\n\n");
    GLFWwindow * window = glfwCreateWindow( 800, 600, "Hello World", NULL, NULL);

    if(!window){
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
                                  
    glewExperimental = GL_TRUE;
    glewInit();

    const GLubyte* renderer   = glGetString(GL_RENDERER);
    const GLubyte* version    = glGetString(GL_VERSION);
    printf("\tRenderer: %s\n", renderer);
    printf("\tOpenGL version supported %s\n", version);

  
    printf("\tend of this 'Program\n\n'");
    glfwTerminate();

    return 0;
}