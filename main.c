#include "functions.h"
 

//~ gcc -Wall -o "%e" "%f" functions.c utils.c ShaderUtils.c Matrix4x.c -lm -lglfw -lGL -lGLEW  

// http://www.songho.ca/opengl/gl_vbo.html#example1

// gcc -Wall -c "%f" functions.c utils.c ShaderUtils.c Matrix4x.c
// gcc -Wall -o "%e" "%f" functions.c utils.c ShaderUtils.c Matrix4x.c -lGLEW -lglfw -lGL -lGLU -lm


// 
// "GLSL/FShader.glsl"
  
int main(void){

  GLuint array[3];

  array[0] = GLSL_Program;
  array[1] = GLSL_vertex;
  array[2] = GLSL_fragment; 

  Init();
  ShaderSetup("GLSL/VShader.glsl", "GLSL/FShader.glsl", array);
  
  Main_Loop();
  Shut_Down(0);
  
  return 0;
}
