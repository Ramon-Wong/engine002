#include "functions.h"


float rotate_z = 0.0f;

const float rotations_per_tick = 0.2f;


GLfloat vertices[]	= {  1.1f, 1.1f, 0.0f,	-1.1f, 1.1f, 0.0f,	-1.1f,-1.1f, 0.0f,	1.1f,-1.1f, 0.0f};
GLfloat Colors[]	= {  1.0f, 1.0f, 1.0f,	 1.0f, 1.0f, 1.0f,	 1.0f, 1.0f, 1.0f,	1.0f, 1.0f, 1.0f};
GLfloat TexCoords[]	= {  0.0f, 0.0f,	     0.0f, 0.0f,	     0.0f, 0.0f,		0.0f, 0.0f};

GLubyte indices[]	= {  0, 1, 2, 2, 3, 0}; 


GLuint GLSL_Prog[3];
GLuint VAO[3];
GLuint VBO[3];
GLuint VCO[3];

void Draw_Object( GLuint, int);

void CheckGLError(){
	GLenum error = glGetError();
	while(error != GL_NO_ERROR) {
		fprintf(stderr, "OpenGL error: %d\n", error);
			// Shutdown();
	}
}


void CS_DrawLine( GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2){

	// glEnableClientState(GL_VERTEX_ARRAY);
	GLfloat Lines[]	= {  x1, y1, z1,	x2, y2, z2};
	GLubyte index[] = {0, 1};

	glVertexPointer(3, GL_FLOAT, 0, Lines);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, index);
	
	// glDisableClientState(GL_VERTEX_ARRAY); // disable vertex arrays

}


void Shutdown(int return_code){
	
	glDeleteBuffers(1, &VAO[2]);
	glDeleteBuffers(1, &VAO[1]);
	glDeleteVertexArrays(1, &VAO[0]);

	glDeleteBuffers(1, &VBO[2]);
	glDeleteBuffers(1, &VBO[1]);
	glDeleteVertexArrays(1, &VBO[0]);

	glDeleteBuffers(1, &VCO[2]);
	glDeleteBuffers(1, &VCO[1]);
	glDeleteVertexArrays(1, &VCO[0]);


	if( GLSL_Prog[0]){
		glDeleteShader( GLSL_Prog[1]);
		glDeleteShader( GLSL_Prog[2]);		
		glDeleteProgram( GLSL_Prog[0]);		
	}

	glfwTerminate();
	exit(return_code);
}


void Main_Loop(void){

	ShaderSetup();
  
	GLSL_Prog[0]		= glCreateProgram();
	GLSL_Prog[1]		= ReadGLSLScript( GLSL_Prog[0], 0, "GLSL/VShader.glsl");
	GLSL_Prog[2]		= ReadGLSLScript( GLSL_Prog[0], 1, "GLSL/FShader.glsl");
	LinkPrograms(GLSL_Prog[0]);

	GLFWwindow * wnd = glfwGetCurrentContext();

	double old_time = glfwGetTime();

	GLfloat		Proj_Matrix[16];
	GLfloat		View_Matrix[16];
	GLfloat		Orth_Matrix[16];
	GLfloat		Orth_View[16];
	GLfloat		Proj_View[16];

	MLoadIdentity(Proj_Matrix);
	MLoadIdentity(View_Matrix);
	MLoadIdentity(Orth_Matrix);
	MLoadIdentity(Orth_View);	
 	MLoadIdentity(Proj_View);

	float View[] = {  0.0f,  0.0f, 12.0f};
	float Pose[] = {  0.0f,  0.0f,  6.0f};
	float Upvx[] = {  0.0f,  1.0f,  0.0f};
	float point[] = { 0.0f, 0.0f, 0.0f};
	int lock = 0;

	LookAtM( View_Matrix, Pose, View, Upvx);
	float aspect_ratio = ((float)600) / 800;
	MFrustum( (float*)Proj_Matrix, 1.5f, -1.5f, -0.5f * aspect_ratio, 0.5f * aspect_ratio, 1.0f, 100.0f);	// Projection is the frustum
	MOrtho( (float*)Orth_Matrix, 0.5f, -0.5f, -0.5f * aspect_ratio, 0.5f * aspect_ratio, 1.0f, 100.0f);		// Orthographic mode      
	MMultiply( Orth_View, Orth_Matrix, View_Matrix);
	MMultiply( Proj_View, Proj_Matrix, View_Matrix);

	while(!glfwWindowShouldClose(wnd)){

		double current_time = glfwGetTime();
		double delta_rotate = (current_time - old_time) * rotations_per_tick * 360;

		rotate_z = 0.1 * delta_rotate;
 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram( GLSL_Prog[0]);

		if(glfwGetKey( wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS){	glfwSetWindowShouldClose( wnd, 1);}
		if(glfwGetKey( wnd, GLFW_KEY_W) == GLFW_PRESS){			MoveCamera( Pose, View,-0.001f);						lock = 0;}
		if(glfwGetKey( wnd, GLFW_KEY_S) == GLFW_PRESS){			MoveCamera( Pose, View, 0.001f);						lock = 0;}
		if(glfwGetKey( wnd, GLFW_KEY_A) == GLFW_PRESS){			RotateCamera( Pose, View,-0.001f, 0.0f, 1.0f, 0.0f);	lock = 0;}
		if(glfwGetKey( wnd, GLFW_KEY_D) == GLFW_PRESS){			RotateCamera( Pose, View, 0.001f, 0.0f, 1.0f, 0.0f);	lock = 0;}
		if(glfwGetKey( wnd, GLFW_KEY_Q) == GLFW_PRESS){			StrafeCamera( Pose, View, -0.005f);						lock = 0;}
		if(glfwGetKey( wnd, GLFW_KEY_E) == GLFW_PRESS){			StrafeCamera( Pose, View,  0.005f);						lock = 0;}

		LookAtM( View_Matrix, Pose, View, Upvx);				// Update Camera
		MMultiply( Proj_View, Proj_Matrix, View_Matrix);

		setPlanes(Proj_View);

		if( lock == 0){
			int v = 0;	
			for(int i = 0; i < 6; i++){
				v += PointinPlane(i, point);
			}

			printf("\n");
			printf( "\n Point in Right	Plane: %i",	PointinPlane( RIGHT,	point));
			printf( "\n Point in Left	Plane: %i",	PointinPlane( LEFT,		point));
			printf( "\n Point in Back	Plane: %i",	PointinPlane( BACK,		point));
			printf( "\n Point in Front	Plane: %i",	PointinPlane( FRONT,	point));
			printf( "\n Point in Top	Plane: %i",	PointinPlane( TOP,		point));
			printf( "\n Point in Bottom Plane: %i",	PointinPlane( BOTTOM,	point));
			printf( "\n Total Value: %i", v );
			printf("\n");
			lock = 1;
		}

		glUniform3f( glGetUniformLocation( GLSL_Prog[0], "RGB"),				0.5f, 1.0f, 0.6f);
		glUniform1f( glGetUniformLocation( GLSL_Prog[0], "PI"),					PI);
		glUniform1f( glGetUniformLocation( GLSL_Prog[0], "rotate_z"),			rotate_z);
		glUniformMatrix4fv( glGetUniformLocation( GLSL_Prog[0], "uProjView"), 		1, GL_FALSE, Proj_View);

		gMatrixTranslation( 0.0, 0.0, 0.0);
		// gMatrixRotation( rotate_z, 0.0, 0.0, 1.0);
		// gMatrixRotation( rotate_z, 0.0, 1.0, 0.0);
		// gMatrixRotation( rotate_z, 1.0, 0.0, 0.0);
		gPopMatrix( GLSL_Prog[0], "ModelMatrix");

		glEnableClientState(GL_VERTEX_ARRAY);
		for(int i = 0; i < 21; i++){

			CS_DrawLine( -10.0f, -2.0f, 10.0f - i,	 10.0f, -2.0f, 10.0f - i);
			CS_DrawLine( -10.0f + i, -2.0f,-10.0f, 	-10.0f + i, -2.0f, 10.0f);

			CS_DrawLine( -10.0f + i, -2.0f,-10.0f,	-10.0f + i, 9.0f,-10.0f);
			CS_DrawLine( -10.0f, -2.0f, 10.0f - i,	-10.0f, 9.0f, 10.0f - i);
			if( i < 11){
				CS_DrawLine( -10.0f, -1.0f + i,-10.0f,	 10.0f, -1.0f + i,-10.0f);
				CS_DrawLine( -10.0f, -1.0f + i,-10.0f,	-10.0f, -1.0f + i, 10.0f);
			}
		}

		glDisableClientState(GL_VERTEX_ARRAY); // disable vertex arrays

		// draw cube
		glEnableClientState(GL_VERTEX_ARRAY);
		glUniform3f( glGetUniformLocation( GLSL_Prog[0], "RGB"),				1.0f, 1.0f, 1.0f);
		gMatrixTranslation( 0.0, 0.0, 0.0);
		// gMatrixRotation( rotate_z, 0.0, 0.0, 1.0);
		// gMatrixRotation( rotate_z, 0.0, 1.0, 0.0);
		// gMatrixRotation( rotate_z, 1.0, 0.0, 0.0);		

		glVertexPointer(3, GL_FLOAT, 0, box_vertices);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, box_indices);
		glDisableClientState(GL_VERTEX_ARRAY); // disable vertex arrays
		// end draw

		glfwSwapBuffers(wnd);
		glfwPollEvents();
		CheckGLError();
	}
}

