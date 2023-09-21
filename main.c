#include "functions.h"


GLFWwindow * window;


int main(int argc, char *argv[]){

    Init();
    Main_Loop();
    Shutdown(0);
    
    return 0;
}


