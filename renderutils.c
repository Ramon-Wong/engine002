#include "functions.h"


static float	    CulRTMatrix[16];
static int		    counter = 0;


void gMatrixRotation( GLfloat angle, GLfloat x, GLfloat y, GLfloat z){

    float Temp[16];

	if( counter == 0){
		MLoadIdentity( CulRTMatrix);
        MRotate( CulRTMatrix, angle, x, y, z);
	}else if( counter > 0){
        MLoadIdentity( Temp);
        MRotate( Temp, angle, x, y, z);
        MMultiply( CulRTMatrix, CulRTMatrix, Temp);
    }

    counter += 1;
}


void gMatrixTranslation( GLfloat x, GLfloat y, GLfloat z){

    float Temp[16];

	if( counter == 0){
		MLoadIdentity( CulRTMatrix);
        MTranslate( CulRTMatrix, x, y, z);
	}else if( counter > 0){
        MLoadIdentity( Temp);
        MTranslate( CulRTMatrix, x, y, z);
        MMultiply( CulRTMatrix, CulRTMatrix, Temp);
    }

    counter += 1;
}


void gPopMatrix(GLuint Prog, const char * uniform){

    glUniformMatrix4fv( glGetUniformLocation( Prog, uniform), 1, GL_FALSE, CulRTMatrix);
	counter = 0;
}


void Draw_Geometry( GLenum shape, GLuint array_buffer, int size){
	glBindVertexArray( array_buffer);
	glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
    // Draw your geometry
	glDrawElements( shape, size, GL_UNSIGNED_BYTE, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}




void    _Init( GLSL_PROGRAM * Prog, const char *, const char *);
void    _EnableProgram( GLSL_PROGRAM * Prog);
void    _DisableProgram( GLSL_PROGRAM * Prog);
void    _Release(GLSL_PROGRAM * Prog);
GLuint  _GetProgram(GLSL_PROGRAM * Prog);  


void GLSLProg_Init(GLSL_PROGRAM * Prog){

    Prog->Init                  = (void (*)(void *, const char *, const char *))_Init;
    Prog->EnableProgram         = (void (*)(void*))_EnableProgram;
    Prog->DisableProgram        = (void (*)(void*))_DisableProgram;
    Prog->Release               = (void (*)(void*))_Release;
    Prog->GetProgram            = (GLuint (*)(void*))_GetProgram;
}


void    _Init( GLSL_PROGRAM * Prog, const char * vertex, const char * fragment){

	Prog->GLSL_Prog[0]		= glCreateProgram();
	Prog->GLSL_Prog[1]		= ReadGLSLScript( Prog->GLSL_Prog[0], 0, vertex);
	Prog->GLSL_Prog[2]		= ReadGLSLScript( Prog->GLSL_Prog[0], 1, fragment);
	LinkPrograms(Prog->GLSL_Prog[0]);
}


void    _EnableProgram(GLSL_PROGRAM * Prog){
    glUseProgram( Prog->GLSL_Prog[0]);
}


void    _DisableProgram(GLSL_PROGRAM * Prog){
    glUseProgram(0);
}


void    _Release(GLSL_PROGRAM * Prog){
	if( Prog->GLSL_Prog[0]){
		glDeleteShader( Prog->GLSL_Prog[1]);
		glDeleteShader( Prog->GLSL_Prog[2]);		
		glDeleteProgram( Prog->GLSL_Prog[0]);		
	}
}


GLuint  _GetProgram(GLSL_PROGRAM * Prog){
    return Prog->GLSL_Prog[0];
}
