#include "functions.h"



        //   (float* Mat, float Left, float Right, float Bottom, float Top, float Near, float Far)
// MFrustum( (float*)Proj_Matrix, left, right, bottom, top, near, far);	// Projection is the frustum
// MOrtho(   (float*)Orth_Matrix, left, right, bottom, top, near, far);		// Orthographic mode     




void    _SetProjection( CAMERA *, float, float, float, float, float, float);
void    _Lookup( CAMERA *, float *, float *, float *);
void    _uProjView( CAMERA *, GLuint, const char *);


void Camera_Init(CAMERA * Cam){

	MLoadIdentity(Cam->Proj_Matrix);
	MLoadIdentity(Cam->View_Matrix);
	MLoadIdentity(Cam->Orth_Matrix);
	MLoadIdentity(Cam->Orth_View);	
 	MLoadIdentity(Cam->Proj_View);    

    Cam->SetProjection          = (void (*)(void *, float, float, float, float, float, float))_SetProjection;
    Cam->Lookup                 = (void (*)(void *, float *, float *, float *))_Lookup;
    Cam->uProjView              = (void (*)(void *, GLuint, const char *))_uProjView;
}


void    _SetProjection( CAMERA * Cam, float left, float right, float bottom, float top, float near, float far){

    MFrustum( (float*)Cam->Proj_Matrix, left, right, bottom, top, near, far);	// Projection is the frustum
    MOrtho(   (float*)Cam->Orth_Matrix, left, right, bottom, top, near, far);	// Orthographic mode     
}


void    _Lookup( CAMERA * Cam, float * pose, float * view, float * upvx){

	LookAtM( Cam->View_Matrix, pose, view, upvx);				// Update Camera
	MMultiply( Cam->Proj_View, Cam->Proj_Matrix, Cam->View_Matrix);
	MMultiply( Cam->Orth_View, Cam->Orth_Matrix, Cam->View_Matrix);
}


 void _uProjView( CAMERA * Cam, GLuint program, const char * tagname){

	glUniformMatrix4fv( glGetUniformLocation( program, tagname), 1, GL_FALSE, Cam->Proj_View);
 }
