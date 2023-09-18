#include "functions.h"

                           

// Define the vertices of the cube
GLfloat box_vertices[] = {  -1.0f,-1.0f, 1.0f,    1.0f,-1.0f, 1.0f,    1.0f, 1.0f, 1.0f,   -1.0f, 1.0f, 1.0f,        // Front face
                            -1.0f,-1.0f,-1.0f,    1.0f,-1.0f,-1.0f,    1.0f, 1.0f,-1.0f,   -1.0f, 1.0f,-1.0f};       // Back face

// Define normals (for lighting calculations)
GLfloat box_normals[] = {    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,        // Front face
                             0.0f, 0.0f,-1.0f,    0.0f, 0.0f,-1.0f,    0.0f, 0.0f,-1.0f,    0.0f, 0.0f,-1.0f,        // Back face
                            -1.0f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,        // Left face    
                             1.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,        // Right face
                             0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 0.0f,        // Top face
                             0.0f,-1.0f, 0.0f,    0.0f,-1.0f, 0.0f,    0.0f,-1.0f, 0.0f,    0.0f,-1.0f, 0.0f};       // Bottom face

GLfloat box_colors[]   = {   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 1.0f,           // v0,v1,v2,v3 (front)
                             1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 1.0f,           // v0,v3,v4,v5 (right)
                             1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f,           // v0,v5,v6,v1 (top)
                             1.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,           // v1,v6,v7,v2 (left)
                             0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f,           // v7,v4,v3,v2 (bottom)
                             0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 1.0f };         // v4,v7,v6,v5 (back)

// Define texture coordinates for each vertex
GLfloat box_texcoords[] = {  0.0f, 0.0f,    1.0f, 0.0f,    1.0f, 1.0f,    0.0f, 1.0f,                                // Front face
                             0.0f, 0.0f,    1.0f, 0.0f,    1.0f, 1.0f,    0.0f, 1.0f,                                // Back face
                             0.0f, 0.0f,    1.0f, 0.0f,    1.0f, 1.0f,    0.0f, 1.0f,                                // Left face
                             0.0f, 0.0f,    1.0f, 0.0f,    1.0f, 1.0f,    0.0f, 1.0f,                                // Right face
                             0.0f, 0.0f,    1.0f, 0.0f,    1.0f, 1.0f,    0.0f, 1.0f,                                // Top face
                             0.0f, 0.0f,    1.0f, 0.0f,    1.0f, 1.0f,    0.0f, 1.0f};                               // Bottom face

// Define the indices 
GLubyte box_indices[] = {    0, 1, 2, 2, 3, 0,                                                                       // Front face
                             4, 5, 6, 6, 7, 4,                                                                       // Back face
                             0, 4, 7, 7, 3, 0,                                                                       // Left face
                             1, 5, 6, 6, 2, 1,                                                                       // Right face
                             3, 2, 6, 6, 7, 3,                                                                       // Top face
                             0, 1, 5, 5, 4, 0};                                                                      // Bottom face

