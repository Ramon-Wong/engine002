#include "functions.h"
 




int main(void){
  Init();
  ShaderSetup();
  
  Main_Loop();
  Shut_Down(0);
  
  return 0;
}
