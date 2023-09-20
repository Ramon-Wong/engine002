#include "functions.h"


const float rotations_per_tick		= 0.2f;
	  float timer					= 0.0f;


GLfloat vertices[]	= {  4.0f, 4.0f, -4.0f, 	
						-4.0f, 4.0f, -4.0f,	
						-4.0f,-4.0f, -4.0f, 	
						 4.0f,-4.0f, -4.0f};	

GLfloat colors[]	= {  1.0f, 0.0f, 0.0f, 		 0.0f, 1.0f, 0.0f,		 0.0f, 0.0f, 1.0f, 		1.0f, 1.0f, 1.0f};	

GLfloat texCoords[] = {	0.0f, 0.0f,   // Top-left
						1.0f, 0.0f,   // Bottom-left
    					1.0f, 1.0f,   // Bottom-left
    					0.0f, 1.0f }; // Bottom-right

GLubyte indices[]	= {  0, 1, 2, 2, 3, 0}; // anti clockwise 

GLFWwindow * wnd;

GLuint				VAO[3];						// Vertice Array Object holding ya, array object, buffer objects.
GLuint				VBO[3];
GLuint				GLSL_Prog[3];				// GLSL Program

float				rot = 0.0f;


void Main_Loop(void){
	double old_time = glfwGetTime();

	GLfloat		Proj_Matrix[16];
	GLfloat		View_Matrix[16];
	GLfloat		ProjView[16];

	MLoadIdentity(Proj_Matrix); 
	MLoadIdentity(View_Matrix); 

	GLSL_Prog[0]		= glCreateProgram();
	GLSL_Prog[1]		= ReadGLSLScript( GLSL_Prog[0], 0, "GLSL/vbShader.glsl");
	GLSL_Prog[2]		= ReadGLSLScript( GLSL_Prog[0], 1, "GLSL/fbShader.glsl");
	LinkPrograms(GLSL_Prog[0]);

	float aspect_ratio = ((float)600) / 800;
	MFrustum( (float*)Proj_Matrix, 0.5f, -0.5f, -0.5f * aspect_ratio, 0.5f * aspect_ratio, 1.0f, 100.0f);	
	
	float View[] = {  0.0f,  0.0f, 12.0f};
	float Pose[] = {  0.0f,  0.0f,  6.0f};
	float Upvx[] = {  0.0f,  1.0f,  0.0f};
	
	LookAtM( View_Matrix, Pose, View, Upvx);

	MMultiply( ProjView, Proj_Matrix, View_Matrix);

	// SetupVAO( &vao, &vbo, &ebo, vertices, colors, indices, sizeof(vertices), sizeof(colors), sizeof(indices));
	SetupVAOArray( &VAO[0], &VAO[1], &VAO[2], vertices, colors, texCoords,
					indices,  sizeof(indices), 
					sizeof(vertices), sizeof(colors), sizeof(texCoords));

	SetupVAOArray( &VBO[0], &VBO[1], &VBO[2], box_vertices, box_normals, box_texcoords,
					box_indices,  sizeof(box_indices), 
					sizeof(box_vertices), sizeof(box_normals), sizeof(box_texcoords));


    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL error: %d\n", error);
		Shut_Down(1);
    }
	// texture setup

	GLuint 		m_texture = LoadTexture( GLSL_Prog[0], "data/skin2.tga", "tSampler", 0);   

	// projection matrix outside the rendering loop
	// GLuint ProjLocation		= glGetUniformLocation( GLSL_Prog[0], "uProjView");

	glUniformMatrix4fv( glGetUniformLocation( GLSL_Prog[0], "uProjView"),			1,	GL_FALSE, ProjView);

// texture setup end

	glEnable(GL_DEPTH_TEST);  
	
	while(!glfwWindowShouldClose(wnd)){

		double current_time = glfwGetTime();
		double delta_rotate = (current_time - old_time) * rotations_per_tick * 360;

		timer = 0.1 * delta_rotate;
		rot += 0.005f;

		if(glfwGetKey( wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS){
			glfwSetWindowShouldClose( wnd, 1);
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUniform1f( glGetUniformLocation( GLSL_Prog[0], "timer"), timer);
		glUniform1f( glGetUniformLocation( GLSL_Prog[0], "frustum_cube"), 0.0f);

		glUseProgram( GLSL_Prog[0]);

		gMatrixTranslation( GLSL_Prog[0], 0.0f, 0.0f, 8.0f);
		gMatrixRotation( GLSL_Prog[0], rot, 0.0f, 0.0f, 1.0f);
		gMatrixRotation( GLSL_Prog[0], rot, 0.0f, 1.0f, 0.0f);
		gMatrixRotation( GLSL_Prog[0], rot, 1.0f, 0.0f, 0.0f);
		gPopMatrix( GLSL_Prog[0], "modelMatrix");

   		glActiveTexture(GL_TEXTURE0);		
		glBindTexture(GL_TEXTURE_2D, m_texture);

		Draw_Object(VBO[0], 36);

		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			fprintf(stderr, "OpenGL error in mainloop: %d\n", error);
			Shut_Down(1);
		}
		glfwSwapBuffers(wnd);
		glfwPollEvents();
	}

	glDeleteTextures(1, &m_texture);
}


//shut down!!
void Shut_Down(int return_code){

	glDeleteBuffers(1, &VAO[2]);
	glDeleteBuffers(1, &VAO[1]);
	glDeleteVertexArrays(1, &VAO[0]);

	glDeleteBuffers(1, &VBO[2]);
	glDeleteBuffers(1, &VBO[1]);
	glDeleteVertexArrays(1, &VBO[0]);

	if( GLSL_Prog[0]){
		glDeleteProgram( GLSL_Prog[0]);
		glDeleteShader( GLSL_Prog[1]);
		glDeleteShader( GLSL_Prog[2]);		
	}	

	glfwTerminate();
	exit(return_code);
}
