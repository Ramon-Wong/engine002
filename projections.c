#include "functions.h"


void          __SetProjection( PROJECTION *, float, float, float, float, float, float);
void		  __SetOrthoGraphic( PROJECTION *, float, float, float, float, float, float);
void          __SetCamera( PROJECTION *, float *, float *, float *); 
void          __Lookup( PROJECTION *);
void     	  __GetProjView(PROJECTION *, float *);
void          __MoveCamera( PROJECTION *, float);
void          __RotateCamera( PROJECTION *, float, float, float, float);
void          __StrafeCamera( PROJECTION *, float);


void          Projection_Init(PROJECTION * Proj){

	MLoadIdentity( Proj->Proj_Matrix);
	MLoadIdentity( Proj->View_Matrix);

    Proj->SetProjection         = (void	(*)(void *, float, float, float, float, float, float))		__SetProjection;
	Proj->SetOrthoGraphic       = (void	(*)(void *, float, float, float, float, float, float))		__SetOrthoGraphic;
    Proj->SetCamera             = (void	(*)(void *, float *, float *, float *))						__SetCamera;
	Proj->Lookup                = (void	(*)(void *))												__Lookup;
	Proj->GetProjView			= (void (*)(void *, float *))										__GetProjView;
	Proj->MoveCamera			= (void	(*)(void *, float))											__MoveCamera;
	Proj->RotateCamera			= (void	(*)(void *, float, float, float, float))					__RotateCamera;
	Proj->StrafeCamera			= (void	(*)(void *, float))											__StrafeCamera;
}


void    __SetProjection( PROJECTION * Proj, float left, float right, float bottom, float top, float near, float far){
    MFrustum( (float*)Proj->Proj_Matrix, left, right, bottom, top, near, far);
}


void    __SetOrthoGraphic( CAMERA * Cam, float left, float right, float bottom, float top, float near, float far){
    MOrtho(   (float*)Cam->Orth_Matrix, left, right, bottom, top, near, far);	// Orthographic mode     
}


void    __SetCamera( PROJECTION * Proj, float * pose, float * view, float * upvx){
	memcpy( Proj->Cam[0], pose, sizeof(float[3]));
	memcpy( Proj->Cam[1], view, sizeof(float[3]));
	memcpy( Proj->Cam[2], upvx, sizeof(float[3]));
}


void	__Lookup( PROJECTION * Proj){
	LookAtM( Proj->View_Matrix, Proj->Cam[0], Proj->Cam[1], Proj->Cam[2]);			// Update Camera
}


void	__GetProjView( PROJECTION * Proj, float * res){
	MMultiply( res, Proj->Proj_Matrix, Proj->View_Matrix);	
}


void	__SubstractVector( float * result, float * Vec1, float * Vec2){
	result[0] = Vec2[0] - Vec1[0];
	result[1] = Vec2[1] - Vec1[1];
	result[2] = Vec2[2] - Vec1[2];
}


void	__AddVector( float * result, float * Vec1, float * Vec2){
	result[0] = Vec2[0] + Vec1[0];
	result[1] = Vec2[1] + Vec1[1];
	result[2] = Vec2[2] + Vec1[2];
}


void	__MoveCamera( PROJECTION * Proj, float spd){

	float Direction[3];
	__SubstractVector( Direction, Proj->Cam[0], Proj->Cam[1]);

	Proj->Cam[0][0]	+= Direction[0] * spd;
	Proj->Cam[0][2]	+= Direction[2] * spd;
	Proj->Cam[1][0]	+= Direction[0] * spd;
	Proj->Cam[1][2]	+= Direction[2] * spd;
}


void    __RotateCamera(  PROJECTION * Proj, float angle, float x, float y, float z){

	float nView[3];
	float Direction[3];
	__SubstractVector( Direction, Proj->Cam[0], Proj->Cam[1]);

	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	nView[0] 	 = (cosTheta + (1 - cosTheta) * x * x)		* Direction[0];
	nView[0] 	+= ((1 - cosTheta) * x * y - z * sinTheta)	* Direction[1];
	nView[0] 	+= ((1 - cosTheta) * x * z + y * sinTheta)	* Direction[2];

	nView[1] 	 = ((1 - cosTheta) * x * y + z * sinTheta)	* Direction[0];
	nView[1] 	+= (cosTheta + (1 - cosTheta) * y * y)		* Direction[1];
	nView[1] 	+= ((1 - cosTheta) * y * z - x * sinTheta)	* Direction[2];

	nView[2] 	 = ((1 - cosTheta) * x * z - y * sinTheta)	* Direction[0];
	nView[2] 	+= ((1 - cosTheta) * y * z + x * sinTheta)	* Direction[1];
	nView[2] 	+= (cosTheta + (1 - cosTheta) * z * z)		* Direction[2];

	__AddVector( Proj->Cam[1], Proj->Cam[0], nView);
}


void    __StrafeCamera(  PROJECTION * Proj, float spd){
	// StrafeCamera( Proj->Cam[0], Proj->Cam[1], spd);
	float Direction[3];
	__SubstractVector( Direction, Proj->Cam[0], Proj->Cam[1]);	

    float right[3];
    CrossProduct(right, Direction, Proj->Cam[2]);
    Normalize(right);

	Proj->Cam[0][0]	+= right[0] * spd;
	Proj->Cam[0][2]	+= right[2] * spd;
	Proj->Cam[1][0]	+= right[0] * spd;
	Proj->Cam[1][2]	+= right[2] * spd;
}