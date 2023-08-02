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

    VECTOR3D vector1 = {.DATA = { 1.0f, 0.0f, 0.0f}};
    VECTOR3D vector2 = {.DATA = { 0.0f, 1.0f, 0.0f}};
    VECTOR3D vector3 = {.DATA = { 0.0f, 0.0f, 1.0f}};
    VECTOR3D result  = {.DATA = { 0.0f, 0.0f, 0.0f}};

    printf("\n");
    printf("Vector1: %f/ %f/ %f/ \n", vector1.DATA[0], vector1.DATA[1], vector1.DATA[2]);
    printf("Vector2: %f/ %f/ %f/ \n", vector2.DATA[0], vector2.DATA[1], vector2.DATA[2]);
    CrossProduct(&result, &vector1, &vector2);
    printf("Results: %f/ %f/ %f/ \n", result.DATA[0],  result.DATA[1],  result.DATA[2]);
    printf("\n");
    printf("Vector1: %f/ %f/ %f/ \n", vector1.DATA[0], vector1.DATA[1], vector1.DATA[2]);
    printf("Vector3: %f/ %f/ %f/ \n", vector3.DATA[0], vector3.DATA[1], vector3.DATA[2]);
    CrossProduct(&result, &vector1, &vector3);
    printf("Results: %f/ %f/ %f/ \n", result.DATA[0],  result.DATA[1],  result.DATA[2]);
    printf("\n");
    printf("Vector2: %f/ %f/ %f/ \n", vector2.DATA[0], vector2.DATA[1], vector2.DATA[2]);
    printf("Vector3: %f/ %f/ %f/ \n", vector3.DATA[0], vector3.DATA[1], vector3.DATA[2]);
    CrossProduct(&result, &vector2, &vector3);  
    printf("Results: %f/ %f/ %f/ \n", result.DATA[0],  result.DATA[1],  result.DATA[2]);
    printf("\n");
    MLoadIdentity(&matrix1);
    MTranslate(&matrix1, 2.0f, 3.0f, 4.0f);
    printf("Matrix1: %f/ %f/ %f/ %f - \n", matrix1.DATA[0],     matrix1.DATA[1],    matrix1.DATA[2],    matrix1.DATA[3]);
    printf("Matrix1: %f/ %f/ %f/ %f - \n", matrix1.DATA[4],     matrix1.DATA[5],    matrix1.DATA[6],    matrix1.DATA[7]);
    printf("Matrix1: %f/ %f/ %f/ %f - \n", matrix1.DATA[8],     matrix1.DATA[9],    matrix1.DATA[10],   matrix1.DATA[11]);
    printf("Matrix1: %f/ %f/ %f/ %f - \n", matrix1.DATA[12],    matrix1.DATA[13],   matrix1.DATA[14],   matrix1.DATA[15]);
    printf("\n");

    MATRIX4X matrixA = {    .DATA = {   1.0f,   2.0f,   3.0f,   4.0f,
                                        5.0f,   6.0f,   7.0f,   8.0f,
                                        9.0f,   10.0f,  11.0f,  12.0f,
                                        13.0f,  14.0f,  15.0f,  16.0f}};

    MATRIX4X matrixB = {    .DATA = {   17.0f,  18.0f,  19.0f,  20.0f,
                                        21.0f,  22.0f,  23.0f,  24.0f,
                                        25.0f,  26.0f,  27.0f,  28.0f,
                                        29.0f,  30.0f,  31.0f,  32.0f}};

    MLoadIdentity(&matrix1);
    MMultiply(&matrix1, matrixB, matrixA);


    MATRIX4X expectedProduct = {.DATA = {   250.0f,     260.0f,     270.0f,     280.0f,
                                            618.0f,     644.0f,     670.0f,     696.0f,
                                            986.0f,     1028.0f,    1070.0f,    1112.0f,
                                            1354.0f,    1412.0f,    1470.0f,    1528.0f}};
    int i, j;
    float tolerance = 0.0001f;

    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            if(fabs(matrix1.DATA[i * 4 + j] - expectedProduct.DATA[i * 4 + j]) > tolerance){
                printf("Error: Matrix1[%d][%d] = %f, expected %f\n", i, j, matrix1.DATA[i * 4 + j], expectedProduct.DATA[i * 4 + j]);
            }else{
                printf("Matrix1[%d][%d] = %f, expected %f\n", i, j, matrix1.DATA[i * 4 + j], expectedProduct.DATA[i * 4 + j]);
            }

        }
    }



    return 0;
}