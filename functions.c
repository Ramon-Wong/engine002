#include "functions.h"


float rotate_z = 0.0f;

const float rotations_per_tick = 0.2f;


GLfloat vertices[]	= {  1.1f, 1.1f, 0.0f,	-1.1f, 1.1f, 0.0f,	-1.1f,-1.1f, 0.0f,	1.1f,-1.1f, 0.0f};
GLfloat Colors[]	= {  1.0f, 1.0f, 1.0f,	 1.0f, 1.0f, 1.0f,	 1.0f, 1.0f, 1.0f,	1.0f, 1.0f, 1.0f};
GLfloat TexCoords[]	= {  0.0f, 0.0f,	     0.0f, 0.0f,	     0.0f, 0.0f,		0.0f, 0.0f};

GLubyte indices[]	= {  0, 1, 2, 2, 3, 0}; 


// GLuint GLSL_Prog[3];
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

	GLfloat Lines[]	= {  x1, y1, z1,	x2, y2, z2};
	GLubyte index[] = {0, 1};

	glVertexPointer(3, GL_FLOAT, 0, Lines);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, index);
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

	glfwTerminate();
	exit(return_code);
}


void Main_Loop(void){

	ShaderSetup();

	GLFWwindow * wnd = glfwGetCurrentContext();

	double old_time = glfwGetTime();

	CAMERA				Camera;

	GLSL_PROGRAM		Prog01;			// Landscape
	GLSL_PROGRAM		Prog02;			// Objects
	GLSL_PROGRAM		Prog03;			// using Orthographics

	RECTANGLE			Rect;

	Camera_Init(&Camera);
	GLSLProg_Init(&Prog01);
	GLSLProg_Init(&Prog02);
	GLSLProg_Init(&Prog03);
	Rectangle_Init(&Rect, 1.0f, 2.0f, 1.0f);	

	float Pose[] = {  0.0f,  0.0f,  6.0f};
	float View[] = {  0.0f,  0.0f, 12.0f}; 
	float Upvx[] = {  0.0f,  1.0f,  0.0f};
	
	float aspect_ratio = ((float)600) / 800;

	Camera.SetProjection( &Camera, 0.5f, -0.5f, -0.5f * aspect_ratio, 0.5f * aspect_ratio, 1.0f, 100.0f);	// NEW SHIT
	Camera.SetOrthoGraphic( &Camera, 3.5f, -3.5f, -3.5f * aspect_ratio, 3.5f * aspect_ratio, 1.0f, 100.0f);	// NEW SHIT
	Camera.SetCamera( &Camera, Pose, View, Upvx);															// also New shit

	Prog01.Init( &Prog01, "GLSL/VShader1.glsl", "GLSL/FShader1.glsl");
	Prog02.Init( &Prog02, "GLSL/VShader2.glsl", "GLSL/FShader2.glsl");
	Prog03.Init( &Prog03, "GLSL/VShader3.glsl", "GLSL/FShader3.glsl");
	Prog03.LoadTexture( &Prog03, "data/skin2.tga", "tSampler", 0);											// Location 0 = gl_Texture0

	int lock = 0;
	float point[] = { 0.0, 0.0, 0.0};

	while(!glfwWindowShouldClose(wnd)){

		double current_time = glfwGetTime();
		double delta_rotate = (current_time - old_time) * rotations_per_tick * 360;

		rotate_z = 0.1 * delta_rotate;
 
		if( lock == 0){
			int v = 0;	
			for(int i = 0; i < 6; i++){
				v += Camera.PointinPlane( &Camera, i, point);
			}

			// printf("\n");
			// printf( "\n Point in Right	Plane: %i",	Camera.PointinPlane( &Camera, RIGHT,	point));
			// printf( "\n Point in Left	Plane: %i",	Camera.PointinPlane( &Camera, LEFT,		point));
			// printf( "\n Point in Back	Plane: %i",	Camera.PointinPlane( &Camera, BACK,		point));
			// printf( "\n Point in Front	Plane: %i",	Camera.PointinPlane( &Camera, FRONT,	point));
			// printf( "\n Point in Top	Plane: %i",	Camera.PointinPlane( &Camera, TOP,		point));    
			// printf( "\n Point in Bottom Plane: %i",	Camera.PointinPlane( &Camera, BOTTOM,	point));
			// printf( "\n Total Value: %i", v );
			// printf("\n");
			lock = 1;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if(glfwGetKey( wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS){	glfwSetWindowShouldClose( wnd, 1);							lock = 0;}
		if(glfwGetKey( wnd, GLFW_KEY_W) == GLFW_PRESS){			Camera.MoveCamera( &Camera, -0.001f);						lock = 0;}
		if(glfwGetKey( wnd, GLFW_KEY_S) == GLFW_PRESS){			Camera.MoveCamera( &Camera,  0.001f);						lock = 0;}
		if(glfwGetKey( wnd, GLFW_KEY_A) == GLFW_PRESS){			Camera.RotateCamera( &Camera,-0.001f, 0.0f, 1.0f, 0.0f);	lock = 0;}
		if(glfwGetKey( wnd, GLFW_KEY_D) == GLFW_PRESS){			Camera.RotateCamera( &Camera, 0.001f, 0.0f, 1.0f, 0.0f);	lock = 0;}
		if(glfwGetKey( wnd, GLFW_KEY_Q) == GLFW_PRESS){			Camera.StrafeCamera( &Camera, -0.005f);						lock = 0;}
		if(glfwGetKey( wnd, GLFW_KEY_E) == GLFW_PRESS){			Camera.StrafeCamera( &Camera,  0.005f); 					lock = 0;}
		Camera.Lookup(&Camera);
		

		Prog01.EnableProgram(&Prog01);
		Prog01.SetUniform3f( &Prog01, "RGB", 		0.5f, 1.0f, 1.0f);
		Prog01.SetUniform1f( &Prog01, "PI",			PI);
		Prog01.SetUniform1i( &Prog01, "Rotatez",	rotate_z);

		Camera.uProjView(&Camera, Prog01.GetProgram(&Prog01), "uProjView");

		Prog01.gPopMatrix( &Prog01, "ModelMatrix");

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
		Prog01.DisableProgram(&Prog01);

		// Use Program 2

		Prog02.EnableProgram(&Prog02);
		Prog02.SetUniform3f( &Prog02, "RGB", 		0.5f, 1.0f, 1.0f);
		Prog02.SetUniform1f( &Prog02, "PI",			PI);
		Prog02.SetUniform1i( &Prog02, "Rotatez",	rotate_z);
		Camera.uProjView( &Camera, Prog02.GetProgram(&Prog02), "uProjView");

		glEnableClientState(GL_VERTEX_ARRAY);									// Enable Vertex Arrays
		
		Prog02.SetUniform3f( &Prog02, "RGB", 		1.0f, 1.0f, 1.0f);
		Prog02.gMatrixTranslation( &Prog02, 0.0, 0.0, 0.0);
		Prog02.gMatrixRotation( &Prog02, rotate_z, 0.0, 0.0, 1.0);
		Prog02.gMatrixRotation( &Prog02, rotate_z, 0.0, 1.0, 0.0);
		Prog02.gMatrixRotation( &Prog02, rotate_z, 1.0, 0.0, 0.0);
		Prog02.gPopMatrix( &Prog02, "ModelMatrix");

		glVertexPointer(3, GL_FLOAT, 0, box_vertices);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, box_indices);
		glDisableClientState(GL_VERTEX_ARRAY); 									// disable Vertex Arrays

		Prog02.DisableProgram(&Prog02);

		Prog03.EnableProgram(&Prog03);
		Prog03.SetUniform3f( &Prog03, "RGB", 		1.0f, 1.0f, 1.0f);
		Camera.oProjView( &Camera, Prog03.GetProgram(&Prog03), "uProjView");	// need seperate camera system!

		Rect.Render(&Rect, 2.0f, 1.0f);

		Prog03.DisableProgram(&Prog03);

		glfwSwapBuffers(wnd);
		glfwPollEvents();
		CheckGLError();
	}

	// clean stuff that is out of the loop.
	Prog01.Release( &Prog01);
	Prog02.Release( &Prog02);
	Prog03.Release( &Prog03);
}

