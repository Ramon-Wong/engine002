#include "functions.h"









int main(int argc, char *argv[]){

    VECTOR3D v1 = {1, 2, 3};
    VECTOR3D v2 = {4, 5, 6};
    VECTOR3D result =  v2 - v1;
    

    printf("Hello World!\n");
    printf("v1 = (%f, %f, %f)\n", v1.x, v1.y, v1.z);
    printf("v2 = (%f, %f, %f)\n", v2.x, v2.y, v2.z);
    printf("v2 - v1 = (%f, %f, %f)\n", result.x, result.y, result.z);
    result.Normalize();
    printf("\nNormalized!");
    printf("\nv2 - v1 = (%f, %f, %f)\n", result.x, result.y, result.z);
    printf("\nNormalized!");    
    result = normalize(v2 - v1);
    printf("\nv2 - v1 = (%f, %f, %f)\n", result.x, result.y, result.z);

    printf("\nCross Product!");
    result.CrossProduct(v1, v2);
    printf("\nCross Product (%f, %f, %f)\n", result.x, result.y, result.z);

    return 0;
}