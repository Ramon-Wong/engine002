#include "functions.h"


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



void    _Init( GLSL_PROGRAM *, const char *, const char *);
void    _EnableProgram( GLSL_PROGRAM *);
void    _DisableProgram( GLSL_PROGRAM *);
void    _Release( GLSL_PROGRAM *);
GLuint  _GetProgram( GLSL_PROGRAM *);

void    _SetUniform3f( GLSL_PROGRAM *, const char *, float, float, float);
void    _SetUniform1f( GLSL_PROGRAM *, const char *, float);
void    _SetUniform1i( GLSL_PROGRAM *, const char *, int);

void    _gMatrixRotation( GLSL_PROGRAM *, float, float, float, float);
void    _gMatrixTranslation( GLSL_PROGRAM *, float, float, float);
void    _gPopMatrix( GLSL_PROGRAM *, const char *);



void GLSLProg_Init(GLSL_PROGRAM * Prog){

    MLoadIdentity( Prog->TransRotMatrix);
    Prog->Counter               = 0;

    Prog->Init                  = (void (*)(void *, const char *, const char *))        _Init;
    Prog->EnableProgram         = (void (*)(void*))                                     _EnableProgram;
    Prog->DisableProgram        = (void (*)(void*))                                     _DisableProgram;
    Prog->Release               = (void (*)(void*))                                     _Release;
    Prog->GetProgram            = (GLuint (*)(void*))                                   _GetProgram;

    Prog->SetUniform3f          = (void (*)(void*, const char *, float, float, float))  _SetUniform3f;
    Prog->SetUniform1f          = (void (*)(void*, const char *, float))                _SetUniform1f;
    Prog->SetUniform1i          = (void (*)(void*, const char *, int))                  _SetUniform1i;

    Prog->gMatrixRotation       = (void (*)(void*, float, float, float, float))         _gMatrixRotation;
    Prog->gMatrixTranslation    = (void (*)(void*, float, float, float))                _gMatrixTranslation;
    Prog->gPopMatrix            = (void (*)(void*, const char *))                       _gPopMatrix;
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


void    _SetUniform3f( GLSL_PROGRAM * Prog, const char * str, float x, float y, float z){
    glUniform3f( glGetUniformLocation( Prog->GLSL_Prog[0], str), x, y, z);
}


void    _SetUniform1f( GLSL_PROGRAM *  Prog, const char * str, float v){
    glUniform1f( glGetUniformLocation( Prog->GLSL_Prog[0], str), v);
}


void    _SetUniform1i( GLSL_PROGRAM *  Prog, const char * str, int v){
    glUniform1i( glGetUniformLocation( Prog->GLSL_Prog[0], str), v);
}


void    _gMatrixRotation( GLSL_PROGRAM * Prog, float angle, float x, float y, float z){
    float Temp[16];

	if( Prog->Counter == 0){
		MLoadIdentity( Prog->TransRotMatrix);
        MRotate( Prog->TransRotMatrix, angle, x, y, z);
	}else if( Prog->Counter > 0){
        MLoadIdentity( Temp);
        MRotate( Temp, angle, x, y, z);
        MMultiply( Prog->TransRotMatrix, Prog->TransRotMatrix, Temp);
    }

    Prog->Counter += 1;
}


void    _gMatrixTranslation( GLSL_PROGRAM * Prog, float x, float y, float z){
    float Temp[16];

	if( Prog->Counter == 0){
		MLoadIdentity( Prog->TransRotMatrix);
        MTranslate( Prog->TransRotMatrix, x, y, z);
	}else if( Prog->Counter > 0){
        MLoadIdentity( Temp);
        MTranslate( Prog->TransRotMatrix, x, y, z);
        MMultiply( Prog->TransRotMatrix, Prog->TransRotMatrix, Temp);
    }

    Prog->Counter += 1;
}


void    _gPopMatrix( GLSL_PROGRAM * Prog, const char * uniform){

    glUniformMatrix4fv( glGetUniformLocation( Prog->GLSL_Prog[0], uniform), 1, GL_FALSE, Prog->TransRotMatrix);
	Prog->Counter = 0;
}