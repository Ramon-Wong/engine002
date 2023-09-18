#include "functions.h"
 

//~ gcc -Wall -o "%e" "%f" functions.c utils.c ShaderUtils.c Matrix4x.c -lm -lglfw -lGL -lGLEW  

// gcc -Wall -c "%f" functions.c utils.c ShaderUtils.c Matrix4x.c
// gcc -Wall -o "%e" "%f" functions.c utils.c ShaderUtils.c Matrix4x.c -lGLEW -lglfw -lGL -lGLU -lm

  
int main(void){
  Init();
  ShaderSetup1();

  Main_Loop();
  Shut_Down(0);
  
  return 0;
}
