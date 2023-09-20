#include "functions.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


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


// void extract_frustum_planes(const float fr[16], Plane pl[6]) {

//   pl[0].x = fr[3] - fr[0];    pl[0].y = fr[7] - fr[4];  pl[0].z = fr[11] - fr[8];   pl[0].d = fr[15] - fr[12];  // Extract the near plane.
//   pl[1].x = fr[3] + fr[0];    pl[1].y = fr[7] + fr[4];  pl[1].z = fr[11] + fr[8];   pl[1].d = fr[15] + fr[12];  // Extract the far plane.
//   pl[2].x = fr[3] - fr[1];    pl[2].y = fr[7] - fr[5];  pl[2].z = fr[11] - fr[9];   pl[2].d = fr[15] - fr[13];  // Extract the left plane.
//   pl[3].x = fr[3] + fr[1];    pl[3].y = fr[7] + fr[5];  pl[3].z = fr[11] + fr[9];   pl[3].d = fr[15] + fr[13];  // Extract the right plane.
//   pl[4].x = fr[3] - fr[2];    pl[4].y = fr[7] - fr[6];  pl[4].z = fr[11] - fr[10];  pl[4].d = fr[15] - fr[14];  // Extract the top plane.
//   pl[5].x = fr[3] + fr[2];    pl[5].y = fr[7] + fr[6];  pl[5].z = fr[11] + fr[10];  pl[5].d = fr[15] + fr[14];  // Extract the bottom plane.
// }

    // left_plane.a =      Matrix.[12] + Matrix.[0]; 
    // left_plane.b =      Matrix.[13] + Matrix.[1]; 
    // left_plane.c =      Matrix.[14] + Matrix.[2]; 
    // left_plane.d =      Matrix.[15] + Matrix.[3];

    // right_plane.a =     Matrix.[12] - Matrix.[0];
    // right_plane.b =     Matrix.[13] - Matrix.[1];
    // right_plane.c =     Matrix.[14] - Matrix.[2];
    // right_plane.d =     Matrix.[15] - Matrix.[3];    

    // top_plane.a =       Matrix.[12] - Matrix.[4];
    // top_plane.b =       Matrix.[13] - Matrix.[5];
    // top_plane.c =       Matrix.[14] - Matrix.[6];
    // top_plane.d =       Matrix.[15] - Matrix.[7];    

    // bottom_plane.a =    Matrix.[12] + Matrix.[4];
    // bottom_plane.b =    Matrix.[13] + Matrix.[5];
    // bottom_plane.c =    Matrix.[14] + Matrix.[6];
    // bottom_plane.d =    Matrix.[15] + Matrix.[7];    

    // near_plane.a =      Matrix.[12] + Matrix._31;
    // near_plane.b =      Matrix.[13] + Matrix._32;
    // near_plane.c =      Matrix.[14] + Matrix._33;
    // near_plane.d =      Matrix.[15] + Matrix._34;
    
    // far_plane.a =       Matrix.[12] - Matrix._31;
    // far_plane.b =       Matrix.[13] - Matrix._32;
    // far_plane.c =       Matrix.[14] - Matrix._33;
    // far_plane.d =       Matrix.[15] - Matrix._34;  
