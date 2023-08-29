#include "functions.h"















void gloadTexture( GLuint * texture, unsigned char * data, int x, int y, int b){

	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if(b == 3) 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,  x, y, 0, GL_RGB,	GL_UNSIGNED_BYTE, data);
	else if (b == 4) 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA,	GL_UNSIGNED_BYTE, data);

}







void SizeOpenGLScreen(int width, int height){
	if(height==0){
		height=1;
	}

	glViewport( 0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 45.0f, (GLfloat)width/(GLfloat)height, .5f ,150.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

