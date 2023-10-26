#include "functions.h"

// #define STB_IMAGE_IMPLEMENTATION
// #include <stb/stb_image.h>


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

	glGenTextures(1, texture);
	glBindTexture( tTarget, *texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
}


char *	ReadFile(const char * path){
	
	//~ usage										<==
	//~ 											<==
	//~ char * txt;									<==
	//~ 											<==	
	//~ txt = ReadFile("GLSL/loremipsum.txt");		<==
	//~ printf(" txt: %s", txt);					<==
	//~ free(txt);									<== memory leak
	//~ 											<==
	
	FILE *	tFile;
	char *	buffer;
	int		lSize;
	
	tFile = fopen( path, "rt");
	if(tFile){
		
		fseek( tFile, 0, SEEK_END);
		lSize = ftell( tFile);
		rewind( tFile);
		
		buffer = (char*) malloc( sizeof(char)*(lSize+1));
		fread( buffer, 1, lSize, tFile);
		buffer[lSize] = '\0';
		
		fclose(tFile);
	}else{
		printf("Error at opening file: %s", path);
	}
	
	return buffer;
}


void _BufferData0( GLenum tBuffer, GLenum tTarget,  int size1, void * data1){
    glBufferData( tBuffer, size1, NULL, tTarget);
    glBufferSubData( tBuffer, 0, size1, data1);
}


void _BufferData1( GLenum tBuffer, GLenum tTarget,  int size1, void * data1, 
                                                    int size2, void * data2){

    glBufferData( tBuffer, size1 + size2, NULL, tTarget);
    glBufferSubData( tBuffer, 0, size1, data1);
    glBufferSubData( tBuffer, size1, size2, data2);
}


void _BufferData2( GLenum tBuffer, GLenum tTarget,  int size1, void * data1, 
                                                    int size2, void * data2, 
                                                    int size3, void * data3){

    glBufferData( tBuffer, size1 + size2 + size3, NULL, tTarget);
    glBufferSubData( tBuffer, 0, size1, data1);
    glBufferSubData( tBuffer, size1, size2, data2);
    glBufferSubData( tBuffer, size2, size3, data3);
}



// Program[1].uBufferObject( &Program[1], sizeof(float[2048]), DataBlock, "Fontmap", GL_STATIC_DRAW);  

// void gBufferObject( unsigned int Program, int count, int size, void * dataArray, const char * tagname, GLenum type) {

//     glGenBuffers( 1, &Prog);
//     glBindBuffer(GL_UNIFORM_BUFFER, Prog);

//     _BufferData0( GL_UNIFORM_BUFFER, type, size, dataArray);

//     GLuint bindingPoint = glGetUniformBlockIndex(Prog, tagname);
//     if (bindingPoint == GL_INVALID_INDEX) {
//         printf("GL_UNIFORM_BUFFER: %s Invalid Index.\n", tagname);
//         return;
//     }

//     glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, Prog);
//     glUniformBlockBinding( Prog, bindingPoint, 0);			// removed Prog->UBOcount
// }


// Create a uniform buffer object
// GLuint ubo;
// glGenBuffers(1, &ubo);
// glBindBuffer(GL_UNIFORM_BUFFER, ubo);

// // Allocate space for the buffer (you need to know the size)
// glBufferData(GL_UNIFORM_BUFFER, sizeof(CameraDataBlock), NULL, GL_DYNAMIC_DRAW);

// // Bind the buffer to the binding point specified in the shader
// glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo);

// // Update the data in the buffer
// glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(CameraDataBlock), &cameraDataBlock);











// void generalBufferObject( unsigned int bufferID, int size, void * dataArray, const char * tagname, GLenum type) {

//     glGenBuffers( 1, &bufferID);
//     glBindBuffer(GL_UNIFORM_BUFFER, bufferID);

//     glBufferData( GL_UNIFORM_BUFFER, size, dataArray, type);

//     glBindBufferBase(GL_UNIFORM_BUFFER, 0, bufferID);
//     glUniformBlockBinding( Prog->GLSL_Prog[0], bindingPoint, Prog->UBOcount);
// }




	// void generateShadowFBO()
	// {
	//   int shadowMapWidth = RENDER_WIDTH * SHADOW_MAP_RATIO;
	//   int shadowMapHeight = RENDER_HEIGHT * SHADOW_MAP_RATIO;
	
	//   GLenum FBOstatus;

	//   // Try to use a texture depth component
	//   glGenTextures(1, &depthTextureId);
	//   glBindTexture(GL_TEXTURE_2D, depthTextureId);

	//   // GL_LINEAR does not make sense for depth texture. However, next tutorial shows usage of GL_LINEAR and PCF
	//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//   // Remove artifact on the edges of the shadowmap
	//   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	//   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

	//   // No need to force GL_DEPTH_COMPONENT24, drivers usually give you the max precision if available
	//   glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
	//   glBindTexture(GL_TEXTURE_2D, 0);

	//   // create a framebuffer object
	//   glGenFramebuffersEXT(1, &fboId);
	//   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboId);

	//   // Instruct openGL that we won't bind a color texture with the currently bound FBO
	//   glDrawBuffer(GL_NONE);
	//   glReadBuffer(GL_NONE);
 
	//   // attach the texture to FBO depth attachment point
	//   glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,GL_TEXTURE_2D, depthTextureId, 0);

	//   // check FBO status
	//   FBOstatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	//   if(FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
	// 	  printf("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n");

	//   // switch back to window-system-provided framebuffer
	//   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	// } data3





// void createDepthMapFBO(GLuint *fbo, GLuint *depthMap, int width, int height){

//     glGenFramebuffers(1, fbo);
//     glBindFramebuffer(GL_FRAMEBUFFER, *fbo);

//     unsigned char * data = NULL;
//     CreateTexture(GL_TEXTURE_2D, depthMap, data, width, height, GL_DEPTH_COMPONENT);

//     glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *depthMap, 0);

//     if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//         printf("Error: Framebuffer is not complete.\n");

//     glBindFramebuffer(GL_FRAMEBUFFER, 0);
// }




void createDepthMapFBO(GLuint *fbo, int width, int height, GLuint * depthMap){
    // Create a framebuffer object
    glGenFramebuffers(1, fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, *fbo);

    // Create a depth texture
    glGenTextures(1, depthMap);
    glBindTexture(GL_TEXTURE_2D, *depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Attach the depth texture to the framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *depthMap, 0);

    // Check if the framebuffer is complete
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("Error: Framebuffer is not complete.\n");

    // Unbind the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}



	// Hold id of the framebuffer for light POV rendering
	// GLuint fboId;
	// Z values will be rendered to this texture when using fboId framebuffer
	// GLuint depthTextureId;
					
	// void generateShadowFBO()
	// {
	//   int shadowMapWidth = RENDER_WIDTH * SHADOW_MAP_RATIO;
	//   int shadowMapHeight = RENDER_HEIGHT * SHADOW_MAP_RATIO;
	
	//   GLenum FBOstatus;

	//   // Try to use a texture depth component
	//   glGenTextures(1, &depthTextureId);
	//   glBindTexture(GL_TEXTURE_2D, depthTextureId);

	//   // GL_LINEAR does not make sense for depth texture. However, next tutorial shows usage of GL_LINEAR and PCF

	//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//   // Remove artifact on the edges of the shadowmap
	//   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	//   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

	//   // No need to force GL_DEPTH_COMPONENT24, drivers usually give you the max precision if available
	//   glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
	//   glBindTexture(GL_TEXTURE_2D, 0);

	//   // create a framebuffer object
	//   glGenFramebuffersEXT(1, &fboId);
	//   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboId);

	//   // Instruct openGL that we won't bind a color texture with the currently bound FBO
	//   glDrawBuffer(GL_NONE);
	//   glReadBuffer(GL_NONE);
 
	//   // attach the texture to FBO depth attachment point
	//   glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,GL_TEXTURE_2D, depthTextureId, 0);

	//   // check FBO status
	//   FBOstatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	//   if(FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
	// 	  printf("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n");

	//   // switch back to window-system-provided framebuffer
	//   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	// }