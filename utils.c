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







