#include "functions.h"



        //   (float* Mat, float Left, float Right, float Bottom, float Top, float Near, float Far)
// MFrustum( (float*)Proj_Matrix, left, right, bottom, top, near, far);	// Projection is the frustum
// MOrtho(   (float*)Orth_Matrix, left, right, bottom, top, near, far);		// Orthographic mode     




void    _SetProjection( CAMERA *, float, float, float, float, float, float);
void    _SetCamera( CAMERA *, float *, float *, float *);
void    _Lookup( CAMERA *);
void    _uProjView( CAMERA *, GLuint, const char *);
void	_MoveCamera( CAMERA * Cam, float spd);

void Camera_Init(CAMERA * Cam){

	MLoadIdentity(Cam->Proj_Matrix);
	MLoadIdentity(Cam->View_Matrix);
	MLoadIdentity(Cam->Orth_Matrix);
	MLoadIdentity(Cam->Orth_View);	
 	MLoadIdentity(Cam->Proj_View);    

    Cam->SetProjection          = (void (*)(void *, float, float, float, float, float, float))_SetProjection;
    Cam->SetCamera              = (void (*)(void *, float *, float *, float *))_SetCamera;
	Cam->Lookup                 = (void (*)(void *))_Lookup;
    Cam->uProjView              = (void (*)(void *, GLuint, const char *))_uProjView;
	Cam->MoveCamera				= (void (*)(void *, float))_MoveCamera;
}


void    _SetProjection( CAMERA * Cam, float left, float right, float bottom, float top, float near, float far){

    MFrustum( (float*)Cam->Proj_Matrix, left, right, bottom, top, near, far);	// Projection is the frustum
    MOrtho(   (float*)Cam->Orth_Matrix, left, right, bottom, top, near, far);	// Orthographic mode     
}


void    _SetCamera( CAMERA * Cam, float * pose, float * view, float * upvx){
	memcpy( Cam->Cam[0], pose, sizeof(float[3]));
	memcpy( Cam->Cam[1], view, sizeof(float[3]));
	memcpy( Cam->Cam[2], upvx, sizeof(float[3]));
}


void    _Lookup( CAMERA * Cam){

	LookAtM( Cam->View_Matrix, Cam->Cam[0], Cam->Cam[1], Cam->Cam[2]);			// Update Camera
	MMultiply( Cam->Proj_View, Cam->Proj_Matrix, Cam->View_Matrix);
	MMultiply( Cam->Orth_View, Cam->Orth_Matrix, Cam->View_Matrix);
}


 void _uProjView( CAMERA * Cam, GLuint program, const char * tagname){

	glUniformMatrix4fv( glGetUniformLocation( program, tagname), 1, GL_FALSE, Cam->Proj_View);
 }


void _MoveCamera( CAMERA * Cam, float spd){
	MoveCamera( Cam->Cam[0], Cam->Cam[1], spd);
}
