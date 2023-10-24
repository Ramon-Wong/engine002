#include "functions.h"


void          __SetProjection( PROJECTION *, float, float, float, float, float, float);
void          __SetOrthoGraphic( PROJECTION *, float, float, float, float, float, float);
void          __SetCamera( PROJECTION *, float *, float *, float *); 
void          __Lookup( PROJECTION *);

GLfloat *     __GetProjView(PROJECTION *);

void          __MouseCamera( PROJECTION *, float, float);
void          __MoveCamera( PROJECTION *, float);
void          __RotateCamera( PROJECTION *, float, float, float, float);
void          __StrafeCamera( PROJECTION *, float);