#include "functions.h"
 

//~ gcc -Wall -o "%e" "%f" functions.c utils.c ShaderUtils.c Matrix4x.c -lm -lglfw -lGL -lGLEW  

// http://www.songho.ca/opengl/gl_vbo.html#example1

// gcc -Wall -c "%f" functions.c utils.c ShaderUtils.c Matrix4x.c
// gcc -Wall -o "%e" "%f" functions.c utils.c ShaderUtils.c Matrix4x.c -lGLEW -lglfw -lGL -lGLU -lm


// 
// "GLSL/FShader.glsl"
  
int main(void){
  Init();
  // ShaderSetup("GLSL/VShader.glsl", "GLSL/FShader.glsl");
  ShaderSetup1();

	GLSL_Program		= glCreateProgram();
	GLSL_vertex			= ReadGLSLScript( GLSL_Program, 0, "GLSL/VShader.glsl");
	GLSL_fragment		= ReadGLSLScript( GLSL_Program, 1, "GLSL/FShader.glsl");
	LinkPrograms(GLSL_Program);
  

  Main_Loop();
  Shut_Down(0);
  
  return 0;
}
