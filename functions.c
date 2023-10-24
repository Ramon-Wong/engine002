#include "functions.h"


CAMERA				Camera;
GLSL_PROGRAM		Prog03;		
RECTANGLE			Rect;
unsigned int		tTexture;


void CheckGLError(){
	GLenum error = glGetError();
	while(error != GL_NO_ERROR) {
		fprintf(stderr, "OpenGL error: %d\n", error);
			// Shutdown();
	}
}


void Shutdown(int return_code){
	
	Prog03.Release( &Prog03);
	glDeleteTextures(1, &tTexture);

	glfwTerminate();
	exit(return_code);
}


void Main_Loop(void){

	ShaderSetup();

	GLFWwindow * wnd = glfwGetCurrentContext();

	Camera_Init(&Camera);
	GLSLProg_Init(&Prog03);
	Rectangle_Init(&Rect, 1.0f, 2.0f, 1.0f);	

	float Pose[] = {  0.0f,  0.0f,  6.0f};
	float View[] = {  0.0f,  0.0f, 12.0f}; 
	float Upvx[] = {  0.0f,  1.0f,  0.0f};
	
	float aspect_ratio = ((float)600) / 800;

	Camera.SetProjection( &Camera, 0.5f, -0.5f, -0.5f * aspect_ratio, 0.5f * aspect_ratio, 1.0f, 100.0f);	// NEW SHIT
	Camera.SetCamera( &Camera, Pose, View, Upvx);															// also New shit

	Prog03.Init( &Prog03, "GLSL/VShader3.glsl", "GLSL/FShader3.glsl");
	Prog03.LoadTexture( &Prog03, "data/font.tga", "tSampler", &tTexture, 0);								// Location 0 = gl_Texture0 && Shader bound

	int lock = 0;
	float point[] = { 0.0, 0.0, 0.0};

	while(!glfwWindowShouldClose(wnd)){
 
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
		
		Prog03.EnableProgram(&Prog03);
		Camera.uProjView( &Camera, Prog03.GetProgram(&Prog03), "uProjView");	// need seperate camera system!

		Prog03.EnableTexture(&Prog03, tTexture, GL_TEXTURE0);					// TEXTURE BINDING!!!
		Rect.Render(&Rect, 0.0f, 0.0f);

		Prog03.DisableTexture(&Prog03);
		Prog03.DisableProgram(&Prog03);

		glfwSwapBuffers(wnd);
		glfwPollEvents();
		CheckGLError();
	}
	// clean stuff that is out of the loop.
}

