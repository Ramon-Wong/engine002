#include "functions.h"



void Shutdown(int return_code){    
  glfwTerminate();
	exit(return_code);
}