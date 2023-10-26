#include "functions.h"

                           

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
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);Rect.RenderInstances(&Rect, 3.0f, 0.82f, 64);
}

