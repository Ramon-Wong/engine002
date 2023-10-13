#include "functions.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

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

void    _LoadTexture( GLSL_PROGRAM *, const char *, const char *, int);
void    _EnableTexture( GLSL_PROGRAM *, GLenum);
void    _DisableTexture( GLSL_PROGRAM *);

void    _uBufferObject( GLSL_PROGRAM *, int, void *, const char *, GLenum);
void    _ObjectUpdate(GLSL_PROGRAM *, int, void *, int, int);



void GLSLProg_Init(GLSL_PROGRAM * Prog){

    MLoadIdentity( Prog->TransRotMatrix);
    Prog->Counter               = 0;

    Prog->Init                  = (void (*)(void *, const char *, const char *))           _Init;
    Prog->EnableProgram         = (void (*)(void*))                                        _EnableProgram;
    Prog->DisableProgram        = (void (*)(void*))                                        _DisableProgram;
    Prog->Release               = (void (*)(void*))                                        _Release;
    Prog->GetProgram            = (GLuint (*)(void*))                                      _GetProgram;

    Prog->SetUniform3f          = (void (*)(void*, const char *, float, float, float))     _SetUniform3f;
    Prog->SetUniform1f          = (void (*)(void*, const char *, float))                   _SetUniform1f;
    Prog->SetUniform1i          = (void (*)(void*, const char *, int))                     _SetUniform1i;

    Prog->gMatrixRotation       = (void (*)(void*, float, float, float, float))            _gMatrixRotation;
    Prog->gMatrixTranslation    = (void (*)(void*, float, float, float))                   _gMatrixTranslation;
    Prog->gPopMatrix            = (void (*)(void*, const char *))                          _gPopMatrix;
    Prog->LoadTexture           = (void (*)(void*, const char *, const char *, int))       _LoadTexture;
    Prog->EnableTexture         = (void (*)(void*, GLenum))                                _EnableTexture;
    Prog->DisableTexture        = (void (*)(void*))                                        _DisableTexture;
    Prog->gTexture              = 0;

    Prog->UBOcount              = 0;
    Prog->uBufferObject         = (void (*)(void*, int, void *, const char *, GLenum))     _uBufferObject;
    Prog->ObjectUpdate          = (void (*)(void*, int, void *, int, int))                 _ObjectUpdate;
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

        if( Prog->gTexture != 0){
            glDeleteTextures(1, &Prog->gTexture);
        }

        if( Prog->UBOcount > 0){
            for(int i = 0; i < MAX_SHADER; i++){
                if( Prog->bufferID[i] != 0){   glDeleteBuffers(1, &Prog->bufferID[i]);}
            }
        }
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


void CreateTexture( GLenum tTarget, GLuint * texture, unsigned char * data, int width, int height, GLenum format){

	glGenTextures(1, texture);
	glBindTexture( tTarget, *texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
}


void    _LoadTexture( GLSL_PROGRAM * Prog, const char * path, const char * tagname, int location){

    int x,y,n;
	printf("\nLoading %s", path);
    unsigned char * data = stbi_load( path, &x, &y, &n, 0);

	if (data == NULL) { 
		printf("\nCan't open tga file");
    } else {

		if(n == 3){
			CreateTexture( GL_TEXTURE_2D, &Prog->gTexture, data, x, y, GL_RGB);
		}else if(n == 4){
			CreateTexture( GL_TEXTURE_2D, &Prog->gTexture, data, x, y, GL_RGBA);
		}

		glUseProgram( Prog->GLSL_Prog[0]);                                                  // Use the shader program

		glBindTexture(GL_TEXTURE_2D, Prog->gTexture);                                    	// Bind your texture to GL_TEXTURE0    
        
		glUniform1i( glGetUniformLocation(  Prog->GLSL_Prog[0], tagname), location);        // 0 corresponds to GL_TEXTURE0
        printf("\n Load texture at %i", Prog->gTexture);

		glBindTexture(GL_TEXTURE_2D, 0);
		printf("\n texture Process %i/%i/%i \n", x, y, n);		
        stbi_image_free(data);
    }
}


void    _EnableTexture( GLSL_PROGRAM * Prog, GLenum location){
  	glActiveTexture( location);
    glBindTexture(GL_TEXTURE_2D, Prog->gTexture);
}


void    _DisableTexture( GLSL_PROGRAM *){
    glBindTexture(GL_TEXTURE_2D, 0);
}



    
void _uBufferObject(GLSL_PROGRAM * Prog, int size, void * dataArray, const char * tagname, GLenum type) {

    glGenBuffers( 1, &Prog->bufferID[Prog->UBOcount]);
    glBindBuffer(GL_UNIFORM_BUFFER, Prog->bufferID[Prog->UBOcount]);

    // glBufferData(GL_UNIFORM_BUFFER, size, dataArray, type);
    // glBufferSubData(GL_UNIFORM_BUFFER, 0, size, dataArray);
    _BufferData0( GL_UNIFORM_BUFFER, type, size, dataArray);
    GLuint bindingPoint = glGetUniformBlockIndex(Prog->GLSL_Prog[0], tagname);
    if (bindingPoint == GL_INVALID_INDEX) {
        printf("GL_UNIFORM_BUFFER: %s Invalid Index.\n", tagname);
        return;
    }

    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, Prog->bufferID[Prog->UBOcount]);
    glUniformBlockBinding( Prog->GLSL_Prog[0], bindingPoint, Prog->UBOcount);
    // glUniformBlockBinding set to Prog->shadercount
    // for Layout bindings
    // glBindBuffer(GL_UNIFORM_BUFFER, 0);

    Prog->UBOcount += 1;
}


void _ObjectUpdate(GLSL_PROGRAM *Prog, int index, void *data, int start, int size){
    glBindBuffer(GL_UNIFORM_BUFFER, Prog->bufferID[index]);
    glBufferSubData(GL_UNIFORM_BUFFER, start, size, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}





