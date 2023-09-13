#include "functions.h"



void Init(void){
 
	if( glfwInit() != GL_TRUE)
	Shut_Down(1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	wnd = glfwCreateWindow( 800, 600, "Hello Triangle", NULL, NULL);

	if(!wnd) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
	
	}

	glfwMakeContextCurrent(wnd);
 
	printf("GL VENDOR:--- %s \n", glGetString(GL_VENDOR));
	printf("GL RENDERER:- %s \n", glGetString(GL_RENDERER));
	printf("GL VERSION:-- %s \n", glGetString(GL_VERSION));
	printf("GL SHADING:-- %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
 
	GLSL_Program		= 0;
	GLSL_fragment		= 0;
	GLSL_vertex			= 0;	

 }

void Shut_Down(int return_code){
		
	if( GLSL_Program){
		glDeleteProgram( GLSL_Program);
		glDeleteShader( GLSL_vertex);
		glDeleteShader( GLSL_fragment);		
	}

	glfwTerminate();
	exit(return_code);
}


// void SetupVAO(GLuint * vao, GLuint * vbo, GLfloat * vertices) {
//     glGenVertexArrays(1, vao);
//     glBindVertexArray(*vao);

//     glGenBuffers(1, vbo);
//     glBindBuffer(GL_ARRAY_BUFFER, *vbo);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

//     // Set up vertex attribute pointers
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
//     glEnableVertexAttribArray(0);

//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);
// }

// void SetupVAO(GLuint * vao, GLuint * vbo, GLuint * ebo, GLfloat * vertices, GLubyte * indices, GLsizei vsize, GLsizei isize){
//     glGenVertexArrays( 1, vao);
// 	glBindVertexArray(*vao);

// 	glGenBuffers( 1, vbo);
//     glBindBuffer(GL_ARRAY_BUFFER, *vbo);
//     glBufferData(GL_ARRAY_BUFFER, vsize, vertices, GL_STATIC_DRAW);

// 	glGenBuffers( 1, ebo);

//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize, indices, GL_STATIC_DRAW);

//     // Set up vertex attribute pointers
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
//     glEnableVertexAttribArray(0);

//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);
// }

// void SetupVAOWithColors(GLuint * vao, GLuint * vbo, GLuint * ebo, GLfloat * vertices, GLfloat * colors, GLubyte * indices, 
//                         GLsizei vsize, GLsizei csize, GLsizei isize) {
                        
//     glGenVertexArrays(1, vao);                                                              //  Generate vertex array here
//     glBindVertexArray(*vao);                                                                //  and Bind vertex array

//     glGenBuffers(1, vbo);                                                                   //  Generate Vertex Buffer
//     glBindBuffer(GL_ARRAY_BUFFER, *vbo);                                                    //  and Bind the Vertex Buffer

//     glBufferData(GL_ARRAY_BUFFER, vsize + csize, NULL, GL_STATIC_DRAW);                     //  Set up the data
//     glBufferSubData(GL_ARRAY_BUFFER, 0, vsize, vertices);                                   //  from 0 ..       =>  vsize, the size of vertices 
//     glBufferSubData(GL_ARRAY_BUFFER, vsize, csize, colors);                                 //  from 0 + vsize  =>  csize, the size of csize

//     glGenBuffers(1, ebo);                                                                   //  Vertice Indices (ebo)
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);                                            //  Bind Vertice array (ebo)
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize, indices, GL_STATIC_DRAW);                  //  Dump the vertice array into ebo

//     // Set up vertex attribute pointers for position
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);         // Link this with the shader
//     glEnableVertexAttribArray(0);                                                           //

//     // Set up vertex attribute pointers for color
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)vsize);     // Link this with the shader
//     glEnableVertexAttribArray(1);                                                           //

//     glBindBuffer(GL_ARRAY_BUFFER, 0);                                                       //  Bind buffer 0
//     glBindVertexArray(0);                                                                   //  Bind Array 0
// }


void _SetupVAO( GLuint * vao, GLuint * vbo, GLuint * ebo){
//
}


void SetupVAO(GLuint * vao, GLuint * vbo, GLuint * ebo, GLfloat * vertices, GLfloat * colors, GLubyte * indices, GLsizei vsize, GLsizei csize, GLsizei isize){
    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    
    glBufferData(GL_ARRAY_BUFFER, vsize + csize, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vsize, vertices);
    glBufferSubData(GL_ARRAY_BUFFER, vsize, csize, colors);

    // glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    // glBufferData(GL_ARRAY_BUFFER, vsize + csize + tsize, NULL, GL_STATIC_DRAW);
    // glBufferSubData(GL_ARRAY_BUFFER, 0, vsize, vertices);
    // glBufferSubData(GL_ARRAY_BUFFER, vsize, csize, colors);
    // glBufferSubData(GL_ARRAY_BUFFER, vsize + csize, tsize, texcoords);

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



// GL_TEXTURE_2D
// GL_TEXTURE_BUFFER
// needs to check on this tutorial => https://riptutorial.com/opengl/example/23675/basics-of-framebuffers


void CreateTexture( GLenum tTarget, GLuint * texture, unsigned char * data, int width, int height, const char * format){

// GL_STENCIL_INDEX     x GL_STENCIL_INDEX      ::  GL_STENCIL_ATTACHMENT
// GL_DEPTH24_STENCIL8  x GL_DEPTH_STENCIL      ::  GL_DEPTH_STENCIL_ATTACHMENT
// GL_RGB               x GL_RGB                ::  GL_COLOR_ATTACHMENT0

    GLenum  format1;
    GLenum  format2;

    if( strcmp(format, "rgb")       == 0){
        format1 = GL_RGB;
        format2 = GL_RGB;
        printf(" setting image to rgb");
    }
    if( strcmp(format, "rgba")      == 0){
        format1 = GL_RGBA;
        format2 = GL_RGBA;
        printf(" setting image to rgba");        
    }
    if( strcmp(format, "depth")     == 0){
        format1 = GL_DEPTH24_STENCIL8;
        format2 = GL_DEPTH_STENCIL;
        printf(" setting image to depth");
    }
    if( strcmp(format, "stencil")   == 0){
        format1 = GL_DEPTH24_STENCIL8;
        format2 = GL_DEPTH_STENCIL;
        printf(" setting image to stencil");
    }

	glGenTextures(1, texture);
    // glActiveTexture(GL_TEXTURE0);
	glBindTexture( tTarget, *texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, format1, width, height, 0, format2, GL_UNSIGNED_BYTE, data);
}

	//   // check FBO status
	//   FBOstatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	//   if(FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
	// 	  printf("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n");

	//   // switch back to window-system-provided framebuffer
	//   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);


// // create texture
// unsigned int texture;
// glGenTextures(1, &texture);
// glBindTexture(GL_TEXTURE_2D, texture);
// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// // create framebuffer object
// unsigned int fbo;
// glGenFramebuffers(1, &fbo);
// glBindFramebuffer(GL_FRAMEBUFFER, fbo);
// glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

// // render to framebuffer object
// // ...

// // copy framebuffer object to texture
// glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
// glReadBuffer(GL_COLOR_ATTACHMENT0);
// int width = /* framebuffer width */;
// int height = /* framebuffer height */;
// unsigned char* data = new unsigned char[width * height * 3];
// glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

// // save texture to file
// stbi_write_png("texture.png", width, height, 3 /* RGB */, data, width * 3);

// delete[] data;



// create texture
// unsigned int texture;
// glGenTextures(1, &texture);
// glBindTexture(GL_TEXTURE_2D, texture);
// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// // create framebuffer object
// unsigned int fbo;
// glGenFramebuffers(1, &fbo);
// glBindFramebuffer(GL_FRAMEBUFFER, fbo);
// glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

// // check framebuffer status
// GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
// if (status != GL_FRAMEBUFFER_COMPLETE) {
//     std::cerr << "Framebuffer is not complete!" << std::endl;
//     exit(EXIT_FAILURE);
// }

// render to framebuffer object
// ...

// copy framebuffer object to texture
// glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
// glReadBuffer(GL_COLOR_ATTACHMENT0);
// int width = /* framebuffer width */;
// int height = /* framebuffer height */;
// unsigned char* data = new unsigned char[width * height * 3];
// glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

// // save texture to file
// stbi_write_png("texture.png", width, height, 3 /* RGB */, data, width * 3);

// delete[] data;




// GLuint depthStencilTexture;

// // Generate and bind the FBO
// glGenFramebuffers(1, &fbo);
// glBindFramebuffer(GL_FRAMEBUFFER, fbo);

// // Create and attach a depth and stencil texture
// glGenTextures(1, &depthStencilTexture);
// glBindTexture(GL_TEXTURE_2D, depthStencilTexture);
// glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
// glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthStencilTexture, 0);


// // Unbind the FBO
// glBindFramebuffer(GL_FRAMEBUFFER, 0);

// GLuint stencilTexture;

// // Generate and bind the FBO
// glGenFramebuffers(1, &fbo);
// glBindFramebuffer(GL_FRAMEBUFFER, fbo);

// // Create and attach a stencil texture
// glGenTextures(1, &stencilTexture);
// glBindTexture(GL_TEXTURE_2D, stencilTexture);
// glTexImage2D(GL_TEXTURE_2D, 0, GL_STENCIL_INDEX, width, height, 0, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, NULL);
// glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, stencilTexture, 0);



// // Unbind the FBO
// glBindFramebuffer(GL_FRAMEBUFFER, 0);


// stencil
// glTexImage2D(GL_TEXTURE_2D, 0, GL_STENCIL_INDEX, width, height, 0, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, NULL);
// glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, stencilTexture, 0);

// Depth
// glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
// glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthStencilTexture, 0);

// Colors
// format = GL_RGBA
// glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
// glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, n_texture, 0);


// GL_STENCIL_INDEX     x GL_STENCIL_INDEX      ::  GL_STENCIL_ATTACHMENT
// GL_DEPTH24_STENCIL8  x GL_DEPTH_STENCIL      ::  GL_DEPTH_STENCIL_ATTACHMENT
// GL_RGB               x GL_RGB                ::  GL_COLOR_ATTACHMENT0












// // Check if the FBO is complete
// if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
//     // Handle error
//     printf("\nFailed in creating Frame Buffer.\n");
// }


// // Check if the FBO is complete
// if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
//     // Handle error
//     printf("\nFailed in creating Frame Buffer.\n");
// }
