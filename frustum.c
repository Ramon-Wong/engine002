#include "functions.h"

static float        gFrustum[6][4];



void NormalizePlane(int side){

	float magnitude = (float)sqrt( gFrustum[side][0] * gFrustum[side][0] + gFrustum[side][1] * gFrustum[side][1] + gFrustum[side][2] * gFrustum[side][2] );

	gFrustum[side][0] /= magnitude;
	gFrustum[side][1] /= magnitude;
	gFrustum[side][2] /= magnitude;
	gFrustum[side][3] /= magnitude; 
}


void SetPlane( float * ProjView, int side, float A, float B, float C, float D){
	gFrustum[side][0]      = ProjView[ 3] + A;          
    gFrustum[side][1]      = ProjView[ 7] + B;
	gFrustum[side][2]      = ProjView[11] + C;
    gFrustum[side][3]      = ProjView[15] + D;

    NormalizePlane(side);
}


void setPlanes( float * ProjView){
    
    SetPlane( ProjView, RIGHT,      -ProjView[0], -ProjView[4], -ProjView[8],  -ProjView[12]);
    SetPlane( ProjView, LEFT,        ProjView[0],  ProjView[4],  ProjView[8],   ProjView[12]);
    SetPlane( ProjView, BOTTOM,      ProjView[1],  ProjView[5],  ProjView[9],   ProjView[13]);
    SetPlane( ProjView, TOP,        -ProjView[1], -ProjView[5], -ProjView[9],  -ProjView[13]);
    SetPlane( ProjView, BACK,       -ProjView[2], -ProjView[6], -ProjView[10], -ProjView[14]);
    SetPlane( ProjView, FRONT,       ProjView[2],  ProjView[6],  ProjView[10],  ProjView[14]);                
}


int PointinPlane( int i, float * vec){
    float sum = (gFrustum[i][0] * vec[0]) + (gFrustum[i][1] * vec[1]) + (gFrustum[i][2] * vec[2]) + gFrustum[i][3];

    if(sum >= 0.0){
        return 1;
    }else{
        return -1;
    }
}