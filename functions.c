#include "functions.h"



GLSL_PROGRAM		Program[2];
PROJECTION			Camera[2];
unsigned int		Texture[2];
RECTANGLE			Rect[2];

GLenum	TEXTURE_MODE[]	= {GL_TEXTURE0, GL_TEXTURE1};


void CheckGLError(){
	GLenum error = glGetError();
	while(error != GL_NO_ERROR) {
		fprintf(stderr, "OpenGL error: %d\n", error);
		Shutdown(0);
		Shutdown(0);
	}
}


void Shutdown(int return_code){
	
	Program[0].Release( &Program[0]);
	Program[1].Release( &Program[1]);

	glDeleteTextures(2, Texture);

	glfwTerminate();
	exit(return_code);
}


void Main_Loop(void){

	ShaderSetup();

	GLFWwindow * wnd = glfwGetCurrentContext();

	Projection_Init(&Camera[0]);
	Projection_Init(&Camera[1]);

	GLSLProg_Init(&Program[0]);
	GLSLProg_Init(&Program[1]);
	Rectangle_Init(&Rect[0], 1.0f, 2.0f, 1.0f);		// size, X, Y location
	Rectangle_Init(&Rect[1], 0.1f, 1.0f, 1.0f);

	float Pose[] = {  0.0f,  0.0f,  6.0f};
	float View[] = {  0.0f,  0.0f, 12.0f}; 
	float Upvx[] = {  0.0f,  1.0f,  0.0f};
	
	float aspect_ratio = ((float)600) / 800;

	float Proj_View[16];
	
	Camera[0].SetProjection( &Camera[0], 0.5f, -0.5f, -0.5f * aspect_ratio, 0.5f * aspect_ratio, 1.0f, 100.0f);	
	Camera[0].SetCamera( &Camera[0], Pose, View, Upvx);

	Camera[1].SetOrthoGraphic( &Camera[1], 0.5f, -0.5f, -0.5f * aspect_ratio, 0.5f * aspect_ratio, 1.0f, 100.0f);	
	Camera[1].SetCamera( &Camera[1], Pose, View, Upvx);

	Program[0].Init( &Program[0], "GLSL/VShader1.glsl", "GLSL/FShader1.glsl");
	Program[1].Init( &Program[1], "GLSL/VShader1.glsl", "GLSL/FShader1.glsl");

	Program[0].LoadTexture( &Program[0], "data/skin2.tga", "tSampler", &Texture[0], 0);			// Location 0 = gl_Texture0 && Shader bound
	Program[1].LoadTexture( &Program[1], "data/skin2.tga", "tSampler", &Texture[1], 1);			// Location 0 = gl_Texture1 && Shader bound

	while(!glfwWindowShouldClose(wnd)){
 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if(glfwGetKey( wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS){	glfwSetWindowShouldClose( wnd, 1);								}
		if(glfwGetKey( wnd, GLFW_KEY_W) == GLFW_PRESS){			Camera[0].MoveCamera(   &Camera[0], -0.001f);					}
		if(glfwGetKey( wnd, GLFW_KEY_S) == GLFW_PRESS){			Camera[0].MoveCamera(   &Camera[0],  0.001f);					}
		if(glfwGetKey( wnd, GLFW_KEY_A) == GLFW_PRESS){			Camera[0].RotateCamera( &Camera[0], -0.001f, 0.0f, 1.0f, 0.0f);	}
		if(glfwGetKey( wnd, GLFW_KEY_D) == GLFW_PRESS){			Camera[0].RotateCamera( &Camera[0],  0.001f, 0.0f, 1.0f, 0.0f);	}
		if(glfwGetKey( wnd, GLFW_KEY_Q) == GLFW_PRESS){			Camera[0].StrafeCamera( &Camera[0], -0.005f);					}
		if(glfwGetKey( wnd, GLFW_KEY_E) == GLFW_PRESS){			Camera[0].StrafeCamera( &Camera[0],  0.005f); 					}

		// Scene 1
		for(int i = 0; i < 2; i++){
			Camera[i].Lookup(&Camera[i]);
			Program[i].EnableProgram(&Program[i]);
			
			MLoadIdentity( Proj_View);
			Camera[i].GetProjView(&Camera[i], Proj_View);
			Program[i].SetUniformMatrix(&Program[i], "uProjView", Proj_View);
			
			Program[i].EnableTexture(&Program[i], Texture[i], TEXTURE_MODE[i]);					// TEXTURE BINDING!!!
			Rect[i].Render(&Rect[i], 0.0f, 0.0f);

			Program[i].DisableTexture(&Program[i]);
			Program[i].DisableProgram(&Program[i]);
		}

		glfwSwapBuffers(wnd);
		glfwPollEvents();
		CheckGLError();
	}
}

