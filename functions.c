#include "functions.h"




VECTOR3D normalize( VECTOR3D v ) {

    float length = sqrt( v.x*v.x + v.y*v.y + v.z*v.z );
    VECTOR3D result = { v.x/length, v.y/length, v.z/length };

    return result;
}


VECTOR3D crossproduct( VECTOR3D v1, VECTOR3D v2 ) {
    VECTOR3D result;
    result.x = v1.y*v2.z - v1.z*v2.y;
    result.y = v1.z*v2.x - v1.x*v2.z;
    result.z = v1.x*v2.y - v1.y*v2.x;
    return result;
}