#include "functions.h"

                           


GLubyte _indices[]	= {  0, 1, 2, 2, 3, 0}; 

void _Render( RECTANGLE *, float, float);
void _RenderInstances( RECTANGLE *, float, float, int);
void _set( RECTANGLE *, float x, float y);

void Rectangle_Init( RECTANGLE * Rect, float width, float height, float x, float y){

    Rect->width             = width;
    Rect->height            = height;
    _set( Rect, x, y);
    Rect->Render            = (void (*)(void *, float, float))_Render;
    Rect->RenderInstances   = (void (*)(void *, float, float, int))_RenderInstances;
}


void _Render( RECTANGLE * Rect, float x, float y){

    _set( Rect, x, y);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, Rect->vertices);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, _indices);
    glDisableClientState(GL_VERTEX_ARRAY);
}


void _RenderInstances( RECTANGLE * Rect, float x, float y, int instances){

    _set( Rect, x, y);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, Rect->vertices);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, _indices, instances);
    glDisableClientState(GL_VERTEX_ARRAY);
}


void _set( RECTANGLE * Rect, float x, float y){
    Rect->vertices[0]  = x + Rect->width;   Rect->vertices[3]  = x - Rect->width;   Rect->vertices[6]  = x - Rect->width;   Rect->vertices[9]  = x + Rect->width;
    Rect->vertices[1]  = y + Rect->height;  Rect->vertices[4]  = y + Rect->height;  Rect->vertices[7]  = y - Rect->height;  Rect->vertices[10] = y - Rect->height;
    Rect->vertices[2]  = 0.0f;              Rect->vertices[5]  = 0.0f;              Rect->vertices[8]  = 0.0f;              Rect->vertices[11] = 0.0f;
}