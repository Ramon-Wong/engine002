#include "functions.h"




VECTOR3D normalize( VECTOR3D v ) {
    float length = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    if (length > 0) {
        v.x /= length; v.y /= length; v.z /= length;
    }
    return v;
}