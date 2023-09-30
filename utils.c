#include "functions.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>




void SetupVAOSingle(    GLuint *vao, GLuint *vbo, GLuint *ebo,
                        GLfloat *vertices, GLubyte *indices,
                        GLsizei vsize, GLsizei isize){
    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);

    // Copy vertex data to the buffer
    glBufferData(GL_ARRAY_BUFFER, vsize, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize, indices, GL_STATIC_DRAW);

    // Set up vertex attribute pointers for position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}




void SetupVAO(  GLuint * vao, GLuint * vbo, GLuint * ebo, 
                GLfloat * vertices, GLfloat * colors, 
                GLubyte * indices, GLsizei vsize, 
                GLsizei csize, GLsizei isize){
    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    
    glBufferData(GL_ARRAY_BUFFER, vsize + csize, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vsize, vertices);
    glBufferSubData(GL_ARRAY_BUFFER, vsize, csize, colors);

    glGenBuffers(1, ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize, indices, GL_STATIC_DRAW);

    // Set up vertex attribute pointers for position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Set up vertex attribute pointers for color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)(intptr_t)vsize);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void SetupVAOArray( GLuint * vao, GLuint * vbo, GLuint * ebo, 
                    GLfloat * array1, GLfloat * array2, GLfloat * array3, 
                    GLubyte * indices, GLsizei size0,
                    GLsizei size1, GLsizei size2, GLsizei size3){

    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    glGenBuffers(1, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, *vbo); 
    glBufferData(GL_ARRAY_BUFFER, size1 + size2 + size3, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER,     0,             size1, array1);
    glBufferSubData(GL_ARRAY_BUFFER, size1,             size2, array2);
    glBufferSubData(GL_ARRAY_BUFFER, size1 + size2,     size3, array3);

    glGenBuffers(1, ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size0, indices, GL_STATIC_DRAW);

    // Set up vertex attribute pointers for array1
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)(intptr_t) 0);
    glEnableVertexAttribArray(0);

    // Set up vertex attribute pointers for array2
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)(intptr_t) size1);
    glEnableVertexAttribArray(1);

    // Set up vertex attribute pointers for array3
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(intptr_t) size1 + size2);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}



void CreateTexture( GLenum tTarget, GLuint * texture, unsigned char * data, int width, int height, GLenum format){

// glTexImage2D(GL_TEXTURE_2D, 0, GL_STENCIL_INDEX,     width, height, 0, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE,       NULL);      Stencil
// glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8,  width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8,   NULL);      Depth
// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,               width, height, 0, GL_RGB,           GL_UNSIGNED_BYTE,       data);      Color

	glGenTextures(1, texture);
	glBindTexture( tTarget, *texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
}



GLuint LoadTexture(GLuint _glslProg, const char * path, const char * tagname, int location){

    int x,y,n;
	printf("\nLoading %s", path);
    unsigned char * data = stbi_load( path, &x, &y, &n, 0);

	if (data == NULL) { 
		printf("\nCan't open tga file");
		return 0;
    } else {
		GLuint			texture;

		if(n == 3){
			CreateTexture( GL_TEXTURE_2D, &texture, data, x, y, GL_RGB);
		}else if(n == 4){
			CreateTexture( GL_TEXTURE_2D, &texture, data, x, y, GL_RGBA);
		}

		glUseProgram( _glslProg);                                                // Use the shader program
		GLuint textureLocation = glGetUniformLocation(  _glslProg, tagname);
		
		glBindTexture(GL_TEXTURE_2D, texture);                                    	// Bind your texture to GL_TEXTURE0    
		glUniform1i(textureLocation, location);                                     // 0 corresponds to GL_TEXTURE0

		stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);
		printf("\n texture Process %i/%i/%i \n", x, y, n);

		return texture;
    }
}



