#include "functions.h"

                           

// Define the vertices of the cube
GLfloat box_vertices[] = {  1.0f, 1.0f, 1.0f,  -1.0f, 1.0f, 1.0f,  -1.0f,-1.0f, 1.0f,   1.0f,-1.0f, 1.0f,   // v0,v1.0fv2,v3 (front)
                            1.0f, 1.0f, 1.0f,   1.0f,-1.0f, 1.0f,   1.0f,-1.0f,-1.0f,   1.0f, 1.0f,-1.0f,   // v0,v3,v4,v5 (right)
                            1.0f, 1.0f, 1.0f,   1.0f, 1.0f,-1.0f,  -1.0f, 1.0f,-1.0f,  -1.0f, 1.0f, 1.0f,   // v0,v5,v6,v1 (top)
                           -1.0f, 1.0f, 1.0f,  -1.0f, 1.0f,-1.0f,  -1.0f,-1.0f,-1.0f,  -1.0f,-1.0f, 1.0f,   // v1.0fv6,v7,v2 (left)
                           -1.0f,-1.0f,-1.0f,   1.0f,-1.0f,-1.0f,   1.0f,-1.0f, 1.0f,  -1.0f,-1.0f, 1.0f,   // v7,v4,v3,v2 (bottom)
                            1.0f,-1.0f,-1.0f,  -1.0f,-1.0f,-1.0f,  -1.0f, 1.0f,-1.0f,   1.0f, 1.0f,-1.0f}; // v4,v7,v6,v5 (back)

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

GLubyte box_indices[]   =     { 0, 1, 2,   2, 3, 0,      // front
                                4, 5, 6,   6, 7, 4,      // right
                                8, 9,10,  10,11, 8,      // top
                               12,13,14,  14,15,12,      // left
                               16,17,18,  18,19,16,      // bottom
                               20,21,22,  22,23,20};    // back


GLfloat grid_lines[]    = { -20.0f, -2.0f, -20.0f,      20.0f, -2.0f, -20.0f,
                            -20.0f, -2.0f,  20.0f,      20.0f, -2.0f,  20.0f};

GLubyte grid_indices[]  = { 0, 1, 2, 3};
                            //  0     1     2       3     4     5       6     7     8      9     10    11  
// GLfloat vertices[]	= {  1.1f, 1.1f, 0.0f,	-1.1f, 1.1f, 0.0f,	-1.1f,-1.1f, 0.0f,	1.1f,-1.1f, 0.0f};


GLubyte _indices[]	= {  0, 1, 2, 2, 3, 0}; 

void _Render( RECTANGLE *, float, float);

void Rectangle_Init( RECTANGLE * Rect, float size, float x, float y){

    Rect->size = size;
    Rect->vertices[0]  = x + size; Rect->vertices[3]  = x - size; Rect->vertices[6]  = x - size; Rect->vertices[9]  = x + size;
    Rect->vertices[1]  = y + size; Rect->vertices[4]  = y + size; Rect->vertices[7]  = y - size; Rect->vertices[10] = y - size;
    Rect->vertices[2]  = 0.0f;     Rect->vertices[5]  = 0.0f;     Rect->vertices[8]  = 0.0f;     Rect->vertices[11] = 0.0f;

    Rect->Render   = (void (*)(void *, float, float))_Render;
}


void _Render( RECTANGLE * Rect, float x, float y){

    Rect->vertices[0]  = x + Rect->size; Rect->vertices[3]  = x - Rect->size; Rect->vertices[6]  = x - Rect->size; Rect->vertices[9]  = x + Rect->size;
    Rect->vertices[1]  = y + Rect->size; Rect->vertices[4]  = y + Rect->size; Rect->vertices[7]  = y - Rect->size; Rect->vertices[10] = y - Rect->size;
    Rect->vertices[2]  = 0.0f;           Rect->vertices[5]  = 0.0f;           Rect->vertices[8]  = 0.0f;           Rect->vertices[11] = 0.0f;

    GLfloat TexCoords[]	= {  0.0f, 0.0f,	1.0f, 0.0f,	     1.0f, 1.0f,	0.0f, 1.0f};

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, Rect->vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, TexCoords);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, _indices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}




/*

GLfloat vertices2[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,   1,-1, 1,   // v0,v1,v2,v3 (front)
                        1, 1, 1,   1,-1, 1,   1,-1,-1,   1, 1,-1,   // v0,v3,v4,v5 (right)
                        1, 1, 1,   1, 1,-1,  -1, 1,-1,  -1, 1, 1,   // v0,v5,v6,v1 (top)
                       -1, 1, 1,  -1, 1,-1,  -1,-1,-1,  -1,-1, 1,   // v1,v6,v7,v2 (left)
                       -1,-1,-1,   1,-1,-1,   1,-1, 1,  -1,-1, 1,   // v7,v4,v3,v2 (bottom)
                        1,-1,-1,  -1,-1,-1,  -1, 1,-1,   1, 1,-1 }; // v4,v7,v6,v5 (back)

// normal array
GLfloat normals2[]  = { 0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,   // v0,v1,v2,v3 (front)
                        1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,   // v0,v3,v4,v5 (right)
                        0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,   // v0,v5,v6,v1 (top)
                       -1, 0, 0,  -1, 0, 0,  -1, 0, 0,  -1, 0, 0,   // v1,v6,v7,v2 (left)
                        0,-1, 0,   0,-1, 0,   0,-1, 0,   0,-1, 0,   // v7,v4,v3,v2 (bottom)
                        0, 0,-1,   0, 0,-1,   0, 0,-1,   0, 0,-1 }; // v4,v7,v6,v5 (back)

// color array
GLfloat colors2[]   = { 1, 1, 1,   1, 1, 0,   1, 0, 0,   1, 0, 1,   // v0,v1,v2,v3 (front)
                        1, 1, 1,   1, 0, 1,   0, 0, 1,   0, 1, 1,   // v0,v3,v4,v5 (right)
                        1, 1, 1,   0, 1, 1,   0, 1, 0,   1, 1, 0,   // v0,v5,v6,v1 (top)
                        1, 1, 0,   0, 1, 0,   0, 0, 0,   1, 0, 0,   // v1,v6,v7,v2 (left)
                        0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,   // v7,v4,v3,v2 (bottom)
                        0, 0, 1,   0, 0, 0,   0, 1, 0,   0, 1, 1 }; // v4,v7,v6,v5 (back)

// index array of vertex array for glDrawElements() & glDrawRangeElement()
GLubyte indices[]  = { 0, 1, 2,   2, 3, 0,      // front
                       4, 5, 6,   6, 7, 4,      // right
                       8, 9,10,  10,11, 8,      // top
                      12,13,14,  14,15,12,      // left
                      16,17,18,  18,19,16,      // bottom
                      20,21,22,  22,23,20 };    // back

*/