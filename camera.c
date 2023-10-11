#include "functions.h"




void    _SetProjection( CAMERA *, float, float, float, float, float, float);
void    _SetOrthoGraphic( CAMERA *, float, float, float, float, float, float);
void    _SetCamera( CAMERA *, float *, float *, float *);
void    _Lookup( CAMERA *);
void    _uProjView( CAMERA *, GLuint, const char *);
void    _oProjView( CAMERA *, GLuint, const char *);
void	_MoveCamera( CAMERA *, float spd);
void    _MouseCamera( CAMERA *, float, float);
void    _RotateCamera(  CAMERA *, float, float, float, float);
void    _StrafeCamera(  CAMERA *, float);

void	_SetPlanes( CAMERA *);
int		_PointinPlane( CAMERA *, int, float *);


void Camera_Init(CAMERA * Cam){

	Cam->MouseCoord[0] = 0.0f;
	Cam->MouseCoord[1] = 0.0f;

	MLoadIdentity(Cam->Proj_Matrix);
	MLoadIdentity(Cam->View_Matrix);
	MLoadIdentity(Cam->Orth_Matrix);
	MLoadIdentity(Cam->Temp_Matrix);
	MLoadIdentity(Cam->Orth_View);
 	MLoadIdentity(Cam->Proj_View);

    Cam->SetProjection          = (void (*)(void *, float, float, float, float, float, float))_SetProjection;
	Cam->SetOrthoGraphic        = (void (*)(void *, float, float, float, float, float, float))_SetOrthoGraphic;
    Cam->SetCamera              = (void (*)(void *, float *, float *, float *))_SetCamera;
	Cam->Lookup                 = (void (*)(void *))_Lookup;
    Cam->uProjView              = (void (*)(void *, GLuint, const char *))_uProjView;
	Cam->oProjView              = (void (*)(void *, GLuint, const char *))_oProjView;
	Cam->MoveCamera				= (void (*)(void *, float))_MoveCamera;
	Cam->MouseCamera			= (void (*)(void *, float, float))_MouseCamera;
	Cam->RotateCamera			= (void (*)(void *, float, float, float, float))_RotateCamera;
	Cam->StrafeCamera			= (void (*)(void *, float))_StrafeCamera;
	Cam->PointinPlane			= (int  (*)(void *, int, float *))_PointinPlane;
}


void    _SetProjection( CAMERA * Cam, float left, float right, float bottom, float top, float near, float far){
    MFrustum( (float*)Cam->Proj_Matrix, left, right, bottom, top, near, far);	// Projection is the frustum
}
 

void    _SetOrthoGraphic( CAMERA * Cam, float left, float right, float bottom, float top, float near, float far){
    MOrtho(   (float*)Cam->Orth_Matrix, left, right, bottom, top, near, far);	// Orthographic mode     
}


void    _SetCamera( CAMERA * Cam, float * pose, float * view, float * upvx){
	memcpy( Cam->Cam[0], pose, sizeof(float[3]));
	memcpy( Cam->Cam[1], view, sizeof(float[3]));
	memcpy( Cam->Cam[2], upvx, sizeof(float[3]));

	LookAtM( Cam->Temp_Matrix, Cam->Cam[0], Cam->Cam[1], Cam->Cam[2]);
}


void	_Lookup( CAMERA * Cam){
	LookAtM( Cam->View_Matrix, Cam->Cam[0], Cam->Cam[1], Cam->Cam[2]);			// Update Camera
	MMultiply( Cam->Orth_View, Cam->Orth_Matrix, Cam->View_Matrix);				// <=move this line to a function like _uProjView
	_SetPlanes( Cam);
}


void	_uProjView( CAMERA * Cam, GLuint program, const char * tagname){
	MMultiply( Cam->Proj_View, Cam->Proj_Matrix, Cam->View_Matrix);	
	glUniformMatrix4fv( glGetUniformLocation( program, tagname), 1, GL_FALSE, Cam->Proj_View);
}


void	_oProjView( CAMERA * Cam, GLuint program, const char * tagname){
	MMultiply( Cam->Proj_View, Cam->Orth_Matrix, Cam->Temp_Matrix);	
	glUniformMatrix4fv( glGetUniformLocation( program, tagname), 1, GL_FALSE, Cam->Proj_View);
}


void	_SubstractVector( float * result, float * Vec1, float * Vec2){
	result[0] = Vec2[0] - Vec1[0];
	result[1] = Vec2[1] - Vec1[1];
	result[2] = Vec2[2] - Vec1[2];
}


void	_AddVector( float * result, float * Vec1, float * Vec2){
	result[0] = Vec2[0] + Vec1[0];
	result[1] = Vec2[1] + Vec1[1];
	result[2] = Vec2[2] + Vec1[2];
}


void	_MoveCamera( CAMERA * Cam, float spd){

	float Direction[3];
	SUBSTRACT_VECTOR(Direction, Cam->Cam[0], Cam->Cam[1]);
	// _SubstractVector( Direction, Cam->Cam[0], Cam->Cam[1]);

	Cam->Cam[0][0]	+= Direction[0] * spd;
	Cam->Cam[0][2]	+= Direction[2] * spd;
	Cam->Cam[1][0]	+= Direction[0] * spd;
	Cam->Cam[1][2]	+= Direction[2] * spd;
}


void    _RotateCamera(  CAMERA * Cam, float angle, float x, float y, float z){

	float nView[3];
	float Direction[3];
	SUBSTRACT_VECTOR(Direction, Cam->Cam[0], Cam->Cam[1]);
	// _SubstractVector( Direction, Cam->Cam[0], Cam->Cam[1]);

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

	_AddVector( Cam->Cam[1], Cam->Cam[0], nView);
}


void    _MouseCamera( CAMERA * Cam, float x, float y){

	float DeltaX = x - Cam->MouseCoord[0];
	float DeltaY = y - Cam->MouseCoord[1];

	float sensitive_x = 0.01f;
	float sensitive_y = 0.01f;

	_RotateCamera(Cam, sensitive_x * DeltaX, 0.0f, 1.0f, 0.0f);
	_RotateCamera(Cam, sensitive_y * DeltaY, 1.0f, 0.0f, 0.0f);

	Cam->MouseCoord[0] = x;
	Cam->MouseCoord[1] = y;
}


void    _StrafeCamera(  CAMERA * Cam, float spd){
	// StrafeCamera( Cam->Cam[0], Cam->Cam[1], spd);
	float Direction[3];
	_SubstractVector( Direction, Cam->Cam[0], Cam->Cam[1]);	

    float right[3];
    CrossProduct(right, Direction, Cam->Cam[2]);
    Normalize(right);

	Cam->Cam[0][0]	+= right[0] * spd;
	Cam->Cam[0][2]	+= right[2] * spd;
	Cam->Cam[1][0]	+= right[0] * spd;
	Cam->Cam[1][2]	+= right[2] * spd;
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


int		_PointinPlane( CAMERA * Cam, int side, float * vec){

    float sum = (Cam->gFrustum[side][0] * vec[0]) + (Cam->gFrustum[side][1] * vec[1]) + (Cam->gFrustum[side][2] * vec[2]) + Cam->gFrustum[side][3];

    if(sum >= 0.0){
        return 1;
    }else{
        return -1;
    }
}