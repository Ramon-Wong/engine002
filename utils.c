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


void SetupVAO(GLuint * vao, GLuint * vbo, GLuint * ebo, GLfloat * vertices, GLfloat * colors, GLubyte * indices, GLsizei vsize, GLsizei csize, GLsizei isize){
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



GLuint LoadTexture(const char * path, const char * tagname, int location){

    int x,y,n;
	printf("\nLoading %s", path);
    unsigned char * data = stbi_load( path, &x, &y, &n, 0);

	if (data == NULL) { 
		printf("\nCan't open tga file");
		return 0;
    } else {
		GLuint			texture;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		if(n == 3) 
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0,  GL_RGB,	GL_UNSIGNED_BYTE, data);
		else if (n == 4) 
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA,	GL_UNSIGNED_BYTE, data);
		// glGenerateMipmap(GL_TEXTURE_2D);

		CreateTexture( GL_TEXTURE_2D, &texture, data, x, y, GL_RGB);

		glUseProgram( GLSL_Program);                                                // Use the shader program
		GLuint textureLocation = glGetUniformLocation(  GLSL_Program, tagname);
		
		glBindTexture(GL_TEXTURE_2D, texture);                                    	// Bind your texture to GL_TEXTURE0    
		glUniform1i(textureLocation, location);                                     // 0 corresponds to GL_TEXTURE0

		stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);
		printf("\n texture Process %i/%i/%i \n", x, y, n);

		return texture;
    }
}



