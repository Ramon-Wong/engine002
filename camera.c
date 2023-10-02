#include "functions.h"




void    _SetProjection( CAMERA *, float, float, float, float, float, float);
void    _SetCamera( CAMERA *, float *, float *, float *);
void    _Lookup( CAMERA *);
void    _uProjView( CAMERA *, GLuint, const char *);
void	_MoveCamera( CAMERA *, float spd);
void    _RotateCamera(  CAMERA *, float, float, float, float);
void    _StrafeCamera(  CAMERA *, float);

void	_SetPlanes( CAMERA *);
int		_PointinFrustum( CAMERA *, int, float *);


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
	Cam->RotateCamera			= (void (*)(void *, float, float, float, float))_RotateCamera;
	Cam->StrafeCamera			= (void (*)(void *, float))_StrafeCamera;
	// Cam->PointinFrustum			= (int  (*)(void *, int, float *))_PointinFrustum;
	Cam->PointinFrustum			= (int  (*)(void *, int, float *))_PointinFrustum;
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


void	_Lookup( CAMERA * Cam){

	LookAtM( Cam->View_Matrix, Cam->Cam[0], Cam->Cam[1], Cam->Cam[2]);			// Update Camera
	MMultiply( Cam->Proj_View, Cam->Proj_Matrix, Cam->View_Matrix);
	MMultiply( Cam->Orth_View, Cam->Orth_Matrix, Cam->View_Matrix);
	_SetPlanes( Cam);
}


void	_uProjView( CAMERA * Cam, GLuint program, const char * tagname){
	glUniformMatrix4fv( glGetUniformLocation( program, tagname), 1, GL_FALSE, Cam->Proj_View);
 }


void	_MoveCamera( CAMERA * Cam, float spd){
	MoveCamera( Cam->Cam[0], Cam->Cam[1], spd);
}


void    _RotateCamera(  CAMERA * Cam, float angle, float x, float y, float z){
	RotateCamera( Cam->Cam[0], Cam->Cam[1], angle, x, y, z);
}


void    _StrafeCamera(  CAMERA * Cam, float spd){
	StrafeCamera( Cam->Cam[0], Cam->Cam[1], spd);
}


void	setPlane( CAMERA * Cam, int side, float A, float B, float C, float D){
	Cam->gFrustum[side][0]	= Cam->Proj_View[ 3] + A;
	Cam->gFrustum[side][1]	= Cam->Proj_View[ 7] + B;
	Cam->gFrustum[side][2]	= Cam->Proj_View[11] + C;
	Cam->gFrustum[side][3]	= Cam->Proj_View[15] + D;
}


void	_SetPlanes( CAMERA * Cam){
	setPlane( Cam, RIGHT,	-Cam->Proj_View[0], -Cam->Proj_View[4], -Cam->Proj_View[8], -Cam->Proj_View[12]);
	setPlane( Cam, LEFT,	 Cam->Proj_View[0],  Cam->Proj_View[4],  Cam->Proj_View[8],  Cam->Proj_View[12]);
	setPlane( Cam, BOTTOM,	 Cam->Proj_View[1],  Cam->Proj_View[5],  Cam->Proj_View[9],  Cam->Proj_View[13]);
	setPlane( Cam, TOP,		-Cam->Proj_View[1], -Cam->Proj_View[5], -Cam->Proj_View[9], -Cam->Proj_View[13]);
	setPlane( Cam, BACK,	-Cam->Proj_View[2], -Cam->Proj_View[6], -Cam->Proj_View[10],-Cam->Proj_View[14]);
	setPlane( Cam, FRONT,	 Cam->Proj_View[2],  Cam->Proj_View[6],  Cam->Proj_View[10], Cam->Proj_View[14]);
}


int		_PointinFrustum( CAMERA * Cam, int side, float * vec){

    float sum = (Cam->gFrustum[side][0] * vec[0]) + (Cam->gFrustum[side][1] * vec[1]) + (Cam->gFrustum[side][2] * vec[2]) + Cam->gFrustum[side][3];

    if(sum >= 0.0){
        return 1;
    }else{
        return -1;
    }
}