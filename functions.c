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
float 				plane[6][4];

void	SetupPlanes(float*);
void	NormalizePlane(float*);
float 	DotProductPlane(float *, float, float, float);

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
	MFrustum( (float*)Proj_Matrix, 0.5f, -0.5f, -0.5f * aspect_ratio, 0.5f * aspect_ratio, 1.0f, 250.0f);	
	
	float View[] = {  0.0f,  0.0f, 10.0f};
	float Pose[] = {  0.0f,  0.0f,  8.0f};
	float Upvx[] = {  0.0f,  1.0f,  0.0f};
	
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

	LookAtM( View_Matrix, Pose, View, Upvx);
	MMultiply( ProjView, Proj_Matrix, View_Matrix);

	glUniformMatrix4fv( glGetUniformLocation( GLSL_Prog[0], "uProjView"),			1,	GL_FALSE, ProjView);

// texture setup end

	glEnable(GL_DEPTH_TEST);  
	
	while(!glfwWindowShouldClose(wnd)){

		LookAtM( View_Matrix, Pose, View, Upvx);
		MMultiply( ProjView, Proj_Matrix, View_Matrix);

		glUniformMatrix4fv( glGetUniformLocation( GLSL_Prog[0], "uProjView"),			1,	GL_FALSE, ProjView);
		SetupPlanes( ProjView);

		for(int i = 0; i < 6; i++){
			 NormalizePlane(plane[i]);
		}

		DotProductPlane( plane[0], 0.0, 0.0, 0.0);


		double current_time = glfwGetTime();
		double delta		= (current_time - old_time) * rotations_per_tick * 360;

		timer = 0.1 * delta;
		rot += 0.005f;

		if(glfwGetKey( wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS){
			glfwSetWindowShouldClose( wnd, 1);
		}

		if(glfwGetKey( wnd, GLFW_KEY_W) == GLFW_PRESS){
			// printf("\n moving foward");
			MoveCamera( Pose, View,-0.001f);
		}

		if(glfwGetKey( wnd, GLFW_KEY_S) == GLFW_PRESS){
			// printf("\n moving backward");
			MoveCamera( Pose, View, 0.001f);
		}

		if(glfwGetKey( wnd, GLFW_KEY_A) == GLFW_PRESS){
			RotateCamera( Pose, View,-0.0015f, 0.0f, 1.0f, 0.0f);
		}

		if(glfwGetKey( wnd, GLFW_KEY_D) == GLFW_PRESS){
			RotateCamera( Pose, View, 0.0015f, 0.0f, 1.0f, 0.0f);			
		}


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUniform1f( glGetUniformLocation( GLSL_Prog[0], "timer"), timer);
		glUniform1f( glGetUniformLocation( GLSL_Prog[0], "frustum_cube"), 0.50f);

		glUseProgram( GLSL_Prog[0]);

		gMatrixTranslation( GLSL_Prog[0], 0.0f, 0.0f, 8.0f);
		// gMatrixRotation( GLSL_Prog[0], rot, 0.0f, 0.0f, 1.0f);
		// gMatrixRotation( GLSL_Prog[0], rot, 0.0f, 1.0f, 0.0f);
		// gMatrixRotation( GLSL_Prog[0], rot, 1.0f, 0.0f, 0.0f);
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


void SetupPlanes(float* uProjView) {

	for (int i = 0; i < 4; i++) {
        plane[0][i] = uProjView[12] + uProjView[0 + i]; // Left Plane
        plane[1][i] = uProjView[12] - uProjView[0 + i]; // Right Plane
        plane[2][i] = uProjView[12] + uProjView[4 + i]; // Bottom Plane
        plane[3][i] = uProjView[12] - uProjView[4 + i]; // Top Plane
        plane[4][i] = uProjView[12] + uProjView[8 + i]; // Near Plane
        plane[5][i] = uProjView[12] - uProjView[8 + i]; // Far Plane
    }
}

void NormalizePlane(float* plane) {
    // Calculate the length of the normal vector (first 3 elements of the plane array)
    float length = sqrt(plane[0] * plane[0] + plane[1] * plane[1] + plane[2] * plane[2]);
    
    if (length != 0.0f) {

        plane[0] /= length;
        plane[1] /= length;
        plane[2] /= length;
    }
}


float DotProductPlane(float * plane, float point1, float point2, float point3 ){

	return	plane[0] * point1 + 
			plane[1] * point2 + 
			plane[2] * point3 + 
			plane[3] * 1.0f;

}