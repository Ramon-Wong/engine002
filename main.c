#include "functions.h"
#include "matrix.h"


int main(int argc, char *argv[]){

    printf("Hello World!\n");
    MATRIX4X matrix1;
    MATRIX4X matrix2;
    MATRIX4X matrix3;

    MLoadIdentity(&matrix1);
    MLoadIdentity(&matrix2);
    MLoadIdentity(&matrix3);

    printf("Matrix1: %f/ %f/ %f/ %f - \n", matrix1.DATA[0],     matrix1.DATA[1],    matrix1.DATA[0],    matrix1.DATA[3]);
    printf("Matrix1: %f/ %f/ %f/ %f - \n", matrix1.DATA[4],     matrix1.DATA[5],    matrix1.DATA[6],    matrix1.DATA[7]);
    printf("Matrix1: %f/ %f/ %f/ %f - \n", matrix1.DATA[8],     matrix1.DATA[9],    matrix1.DATA[10],   matrix1.DATA[11]);
    printf("Matrix1: %f/ %f/ %f/ %f - \n", matrix1.DATA[12],    matrix1.DATA[13],   matrix1.DATA[14],   matrix1.DATA[15]);
    printf("\n");



    return 0;
}