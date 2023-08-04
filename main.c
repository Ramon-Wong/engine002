#include "functions.h"
#include "matrix.h"



int main(int argc, char *argv[]){

    float Mat[16] = {   1.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f};

    float Pose[3] = {0.0f, 0.0f, 0.0f};
    float View[3] = {0.0f, 0.0f, 1.0f};
    float UpVx[3] = {0.0f, 1.0f, 0.0f};


    LookAtM( Mat, Pose, View, UpVx);


    printf("Hello World!\n");

    return 0;
}