#include "functions.h"


float rotate_z = 0.0f;

const float rotations_per_tick = 0.2f;


GLfloat vertices[]	= {  10.1f,-1.5f, 10.1f,	-10.1f,-1.5f, 10.1f,	-10.1f,-1.5f,-10.1f,	10.1f,-1.5f,-10.1f};
GLfloat Colors[]	= {  1.0f, 1.0f, 1.0f,	 1.0f, 1.0f, 1.0f,	 1.0f, 1.0f, 1.0f,	1.0f, 1.0f, 1.0f};
GLfloat TexCoords[]	= {  0.0f, 0.0f,	     0.0f, 0.0f,	     0.0f, 0.0f,		0.0f, 0.0f};

GLubyte indices[]	= {  0, 1, 2, 2, 3, 0}; 


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
	
	glfwTerminate();
	exit(return_code);
}


void Main_Loop(void){

	ShaderSetup();
	glEnable(GL_DEPTH_TEST);

	GLFWwindow * wnd = glfwGetCurrentContext();

	// double old_time = glfwGetTime();

	CAMERA				Camera;

	GLSL_PROGRAM		Prog01;			// Landscape
	GLSL_PROGRAM		Prog02;			// Objects

	RECTANGLE			Rect;

	Camera_Init(&Camera);
	GLSLProg_Init(&Prog01);
	GLSLProg_Init(&Prog02);
	Rectangle_Init(&Rect, 1.5f, 1.60f, 0.8f);	

	float aspect_ratio = 0.0f;
	aspect_ratio = ((float)600) / 800;
	float Z = 20.0f;

	float Pose[] = {  0.0f,  0.0f,  6.0f + Z};
	float View[] = {  0.0f,  0.5f,  9.0f + Z}; 
	float Upvx[] = {  0.0f,  1.0f,  0.0f};
	
	Camera.SetProjection( &Camera, 0.5f, -0.5f, -0.5f * aspect_ratio, 0.5f * aspect_ratio, 1.25f, 100.0f);	// NEW SHIT
	Camera.SetOrthoGraphic( &Camera, 3.5f, -3.5f, -3.5f * aspect_ratio, 3.5f * aspect_ratio, 1.0f, 100.0f);	// NEW SHIT
	Camera.SetCamera( &Camera, Pose, View, Upvx);															// also New shit

	Prog01.Init( &Prog01, "GLSL/VShader1.glsl", "GLSL/FShader1.glsl");
	Prog02.Init( &Prog02, "GLSL/VShader2.glsl", "GLSL/FShader2.glsl");
	Prog02.LoadTexture( &Prog02, "data/shade.tga", "tSampler", 0);			// ???
	Camera.uProjView( &Camera, Prog02.GetProgram(&Prog02), "uProjView");

	int lock = 0;
	float point[] = { 0.0, 0.0, 0.0};

	while(!glfwWindowShouldClose(wnd)){

		rotate_z = 45.0;
 
		if( lock == 0){
			int v = 0;	
			for(int i = 0; i < 6; i++){
				v += Camera.PointinPlane( &Camera, i, point);
			}

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
		
		// Prog03.EnableBufferObj(&Prog03);				// Eh capture the whole screen?

		// Prog01.EnableProgram(&Prog01);
		// Prog01.SetUniform3f( &Prog01, "RGB", 		0.5f, 1.0f, 1.0f);
		// Prog01.SetUniform1f( &Prog01, "PI",			PI);
		// Prog01.SetUniform1i( &Prog01, "Rotatez",	rotate_z);

		// Camera.uProjView(&Camera, Prog01.GetProgram(&Prog01), "uProjView");

		// Prog01.gPopMatrix( &Prog01, "ModelMatrix");

		// glEnableClientState(GL_VERTEX_ARRAY);
		// for(int i = 0; i < 21; i++){

		// 	CS_DrawLine( -10.0f, -2.0f, (10.0f - i) + Z,	 10.0f, -2.0f, (10.0f - i) + Z);
		// 	CS_DrawLine( -10.0f + i, -2.0f,-10.0f + Z, 		-10.0f + i, -2.0f, 10.0f + Z);

		// 	CS_DrawLine( -10.0f + i, -2.0f,-10.0f + Z,		-10.0f + i, 9.0f,-10.0f  + Z);
		// 	CS_DrawLine( -10.0f, -2.0f, (10.0f - i) + Z,	-10.0f, 9.0f, 10.0f - i  + Z);
		// 	if( i < 11){
		// 		CS_DrawLine( -10.0f, -1.0f + i,-10.0f + Z,	 10.0f, -1.0f + i,-10.0f  + Z);
		// 		CS_DrawLine( -10.0f, -1.0f + i,-10.0f + Z,	-10.0f, -1.0f + i, 10.0f  + Z);
		// 	}
		// }

		// glDisableClientState(GL_VERTEX_ARRAY); // disable vertex arrays
		// Prog01.DisableProgram(&Prog01);

		// Use Program 2
		// *************************************'
		// Scene!!
		// *************************************'

		Prog02.EnableProgram(&Prog02);											// Enable GLSL_Program 2
		Prog02.SetUniform3f( &Prog02, "RGB", 		0.5f, 1.0f, 1.0f);
		Prog02.SetUniform1f( &Prog02, "PI",			PI);
		Prog02.SetUniform1i( &Prog02, "Rotatez",	rotate_z);
		Prog02.EnableTexture(&Prog02, GL_TEXTURE0);
		
		glEnableClientState(GL_VERTEX_ARRAY);									// Enable Vertex Arrays
		
		Prog02.SetUniform3f( &Prog02, "RGB", 		1.0f, 1.0f, 1.0f);
		Prog02.gMatrixTranslation( &Prog02, 0.0f, -0.5f, Z);
		Prog02.gMatrixRotation( &Prog02, rotate_z, 0.0f, 0.0f, 1.0f);
		Prog02.gMatrixRotation( &Prog02, rotate_z, 0.0f, 1.0f, 0.0f);
		Prog02.gMatrixRotation( &Prog02, rotate_z, 1.0f, 0.0f, 0.0f);
		Prog02.gPopMatrix( &Prog02, "ModelMatrix");

		glVertexPointer(3, GL_FLOAT, 0, box_vertices);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, box_indices);
		glDisableClientState(GL_VERTEX_ARRAY); 									// disable Vertex Arrays
		Prog02.DisableProgram(&Prog02);

		Prog02.EnableProgram(&Prog02);											// Enable GLSL_Program 2
		Prog02.gMatrixTranslation( &Prog02, 0.0f, -0.0f, Z);
		Prog02.gPopMatrix( &Prog02, "ModelMatrix");
		Camera.uProjView( &Camera, Prog02.GetProgram(&Prog02), "uProjView");

		glEnableClientState(GL_VERTEX_ARRAY);									// Enable Vertex Arrays
		
		Prog02.SetUniform3f( &Prog02, "RGB", 		1.0f, 1.0f, 1.0f);
		Prog02.gMatrixTranslation( &Prog02, 0.0f, -0.5f, Z);
		Prog02.gPopMatrix( &Prog02, "ModelMatrix");

		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
		glDisableClientState(GL_VERTEX_ARRAY); 									// disable Vertex Arrays
		Prog02.DisableTexture(&Prog02);
		Prog02.DisableProgram(&Prog02); 										// disable GLSL_Program 2
		

		// Use Program 2
		// *************************************'
		// End of Scene!!
		// *************************************'


		glfwSwapBuffers(wnd);
		glfwPollEvents();
		CheckGLError();
	}
	// clean stuff that is out of the loop.
	Prog01.Release( &Prog01);
	Prog02.Release( &Prog02);
}


