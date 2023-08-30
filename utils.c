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
                        
//     glGenVertexArrays(1, vao);
//     glBindVertexArray(*vao);

//     glGenBuffers(1, vbo);
//     glBindBuffer(GL_ARRAY_BUFFER, *vbo);

//     glBufferData(GL_ARRAY_BUFFER, vsize + csize, NULL, GL_STATIC_DRAW);
//     glBufferSubData(GL_ARRAY_BUFFER, 0, vsize, vertices);
//     glBufferSubData(GL_ARRAY_BUFFER, vsize, csize, colors);

//     glGenBuffers(1, ebo);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize, indices, GL_STATIC_DRAW);

//     // Set up vertex attribute pointers for position
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
//     glEnableVertexAttribArray(0);

//     // Set up vertex attribute pointers for color
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)vsize);
//     glEnableVertexAttribArray(1);

//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);
// }
void SetupVAOWithColors(GLuint * vao, GLuint * vbo, GLuint * ebo, GLfloat * vertices, GLfloat * colors, GLubyte * indices, GLsizei vsize, GLsizei csize, GLsizei isize){
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













