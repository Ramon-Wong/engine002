#include "functions.h"


GLfloat box_vertices[] = {  4.0f, 4.0f, 4.0f,  -4.0f, 4.0f, 4.0f,  -4.0f,-4.0f, 4.0f,   4.0f,-4.0f, 4.0f,   // v0,v1,v2,v3 (front)
                            4.0f, 4.0f, 4.0f,   4.0f,-4.0f, 4.0f,   4.0f,-4.0f,-4.0f,   4.0f, 4.0f,-4.0f,   // v0,v3,v4,v5 (right)
                            4.0f, 4.0f, 4.0f,   4.0f, 4.0f,-4.0f,  -4.0f, 4.0f,-4.0f,  -4.0f, 4.0f, 4.0f,   // v0,v5,v6,v1 (top)
                           -4.0f, 4.0f, 4.0f,  -4.0f, 4.0f,-4.0f,  -4.0f,-4.0f,-4.0f,  -4.0f,-4.0f, 4.0f,   // v1,v6,v7,v2 (left)
                           -4.0f,-4.0f,-4.0f,   4.0f,-4.0f,-4.0f,   4.0f,-4.0f, 4.0f,  -4.0f,-4.0f, 4.0f,   // v7,v4,v3,v2 (bottom)
                            4.0f,-4.0f,-4.0f,  -4.0f,-4.0f,-4.0f,  -4.0f, 4.0f,-4.0f,   4.0f, 4.0f,-4.0f }; // v4,v7,v6,v5 (back)

// normal array
GLfloat box_normals[]  = {  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   // v0,v1,v2,v3 (front)
                            1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   // v0,v3,v4,v5 (right)
                            0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   // v0,v5,v6,v1 (top)
                           -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,   // v1,v6,v7,v2 (left)
                            0.0f,-1.0f, 0.0f,   0.0f,-1.0f, 0.0f,   0.0f,-1.0f, 0.0f,   0.0f,-1.0f, 0.0f,   // v7,v4,v3,v2 (bottom)
                            0.0f, 0.0f,-1.0f,   0.0f, 0.0f,-1.0f,   0.0f, 0.0f,-1.0f,   0.0f, 0.0f,-1.0f }; // v4,v7,v6,v5 (back)

// color array
GLfloat box_colors[]   = {  1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 1.0f,   // v0,v1,v2,v3 (front)
                            1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 1.0f,   // v0,v3,v4,v5 (right)
                            1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   // v0,v5,v6,v1 (top)
                            1.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   // v1,v6,v7,v2 (left)
                            0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f,   // v7,v4,v3,v2 (bottom)
                            0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 1.0f }; // v4,v7,v6,v5 (back)

// index array of vertex array for glDrawElements() & glDrawRangeElement()
GLubyte box_indices[]  = {  0, 1, 2,       2, 3, 0,      // front
                            4, 5, 6,       6, 7, 4,      // right
                            8, 9,10,      10,11, 8,      // top
                           12,13,14,      14,15,12,      // left
                           16,17,18,      18,19,16,      // bottom
                           20,21,22,      22,23,20 };    // back


