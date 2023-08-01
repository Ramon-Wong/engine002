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

    printf("Matrix1: %f/ %f/ %f/ %f - \n", matrix1.DATA[0],     matrix1.DATA[1],    matrix1.DATA[2],    matrix1.DATA[3]);
    printf("Matrix1: %f/ %f/ %f/ %f - \n", matrix1.DATA[4],     matrix1.DATA[5],    matrix1.DATA[6],    matrix1.DATA[7]);
    printf("Matrix1: %f/ %f/ %f/ %f - \n", matrix1.DATA[8],     matrix1.DATA[9],    matrix1.DATA[10],   matrix1.DATA[11]);
    printf("Matrix1: %f/ %f/ %f/ %f - \n", matrix1.DATA[12],    matrix1.DATA[13],   matrix1.DATA[14],   matrix1.DATA[15]);
    printf("\n");
    printf("Matrix2: %f/ %f/ %f/ %f - \n", matrix2.DATA[0],     matrix2.DATA[1],    matrix2.DATA[2],    matrix2.DATA[3]);
    printf("Matrix2: %f/ %f/ %f/ %f - \n", matrix2.DATA[4],     matrix2.DATA[5],    matrix2.DATA[6],    matrix2.DATA[7]);
    printf("Matrix2: %f/ %f/ %f/ %f - \n", matrix2.DATA[8],     matrix2.DATA[9],    matrix2.DATA[10],   matrix2.DATA[11]);
    printf("Matrix2: %f/ %f/ %f/ %f - \n", matrix2.DATA[12],    matrix2.DATA[13],   matrix2.DATA[14],   matrix2.DATA[15]);
    printf("\n");
    printf("Matrix3: %f/ %f/ %f/ %f - \n", matrix3.DATA[0],     matrix3.DATA[1],    matrix3.DATA[2],    matrix3.DATA[3]);
    printf("Matrix3: %f/ %f/ %f/ %f - \n", matrix3.DATA[4],     matrix3.DATA[5],    matrix3.DATA[6],    matrix3.DATA[7]);
    printf("Matrix3: %f/ %f/ %f/ %f - \n", matrix3.DATA[8],     matrix3.DATA[9],    matrix3.DATA[10],   matrix3.DATA[11]);
    printf("Matrix3: %f/ %f/ %f/ %f - \n", matrix3.DATA[12],    matrix3.DATA[13],   matrix3.DATA[14],   matrix3.DATA[15]);



    return 0;
}