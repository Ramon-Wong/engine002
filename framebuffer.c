#include "functions.h"


void    __CreateDepthMapFBO( FRAMEBUFFER_OBJECT *, int, int);
void    __CreateColorMapFBO( FRAMEBUFFER_OBJECT *, int, int);
void    __EnableBufferObj( FRAMEBUFFER_OBJECT *);
void    __DisableBufferObj( FRAMEBUFFER_OBJECT *); 
void    __BindTexture( FRAMEBUFFER_OBJECT *, GLenum); 
void    __Release( FRAMEBUFFER_OBJECT *); 



void                FrameBuffer_Init(FRAMEBUFFER_OBJECT * FB_OBJ){

    FB_OBJ->CreateDepthMapFBO       = (void (*)(void*, int, int))           __CreateDepthMapFBO;
    FB_OBJ->CreateColorMapFBO       = (void (*)(void*, int, int))           __CreateColorMapFBO;

    FB_OBJ->EnableBufferObj         = (void (*)(void*))                     __EnableBufferObj;
    FB_OBJ->DisableBufferObj        = (void (*)(void*))                     __DisableBufferObj;
    FB_OBJ->BindTexture             = (void (*)(void*, GLenum))             __BindTexture;

    FB_OBJ->Release                 = (void (*)(void*))                     __Release;
}


void __CreateXTexture( GLuint * texture, unsigned char * DATA, int width, int height, GLenum format, GLenum type){

	glGenTextures( 1, texture);
	glBindTexture( GL_TEXTURE_2D, *texture);

    glTexImage2D( GL_TEXTURE_2D, 0, format, width, height, 0, format, type, DATA);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}


void    __CreateDepthMapFBO( FRAMEBUFFER_OBJECT * FB_OBJ, int width, int height){

    glGenFramebuffers(1, &FB_OBJ->fBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, FB_OBJ->fBuffer);

    __CreateXTexture( &FB_OBJ->gTexture, NULL, width, height, GL_DEPTH_COMPONENT, GL_FLOAT);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, FB_OBJ->gTexture, 0);
    // Check if the framebuffer is complete
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("Error: Framebuffer is not complete.\n");
    // Unbind the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void    __CreateColorMapFBO( FRAMEBUFFER_OBJECT * FB_OBJ, int width, int height){

    glGenFramebuffers(1, &FB_OBJ->fBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, FB_OBJ->fBuffer);

    __CreateXTexture( &FB_OBJ->gTexture, NULL, width, height, GL_RGBA, GL_UNSIGNED_BYTE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FB_OBJ->gTexture, 0);
    // Check if the framebuffer is complete
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("Error: Framebuffer is not complete.\n");
    // Unbind the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void    __EnableBufferObj( FRAMEBUFFER_OBJECT * FB_OBJ){
    glBindFramebuffer(GL_FRAMEBUFFER, FB_OBJ->fBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void    __DisableBufferObj( FRAMEBUFFER_OBJECT * FB_OBJ){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void    __BindTexture( FRAMEBUFFER_OBJECT * FB_OBJ, GLenum location){
  	glActiveTexture( location);
    glBindTexture(GL_TEXTURE_2D, FB_OBJ->gTexture);
}


void    __Release( FRAMEBUFFER_OBJECT * FB_OBJ){

    if( FB_OBJ->gTexture != 0){
        glDeleteTextures(1, &FB_OBJ->gTexture);
    }    
}