#include "functions.h"




int main(int argc, char *argv[]){

    VECTOR3D v1 = {1, 2, 3};
    VECTOR3D v2 = {4, 5, 6};

    VECTOR3D result = normalize(crossproduct(v2, v1));
    printf(" Result: %f %f %f \n", result.x, result.y, result.z);

    result =  normalize(v2 - v1);
    printf(" Result: %f %f %f \n", result.x, result.y, result.z);


    printf("\nTest 1\n");
    result = normalize(v1);
    printf(" Result: %f %f %f \n", result.x, result.y, result.z);

    printf("\nTest 2\n");
    result = normalize(v2);
    printf(" Result: %f %f %f \n", result.x, result.y, result.z);


    return 0;
}