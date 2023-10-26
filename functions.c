#include "functions.h"



GLSL_PROGRAM		Program[2];
PROJECTION			Camera[2];
unsigned int		Texture[2];
RECTANGLE			Rect[2];

GLenum	TEXTURE_MODE[]	= {GL_TEXTURE0, GL_TEXTURE1};
int		DrawInstance[]  = { 1, 64};

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


void StrtoArray(const char *string, int *array, int array_size) {
    int str_len = strlen(string);
    for (int i = 0; i < array_size; i++) {
        if (i < str_len) {
            array[i] = (int)string[i] - 32;
        } else {
            // If we've reached the end of the string, fill the rest with -1
            array[i] = -1;
        }
    }
}


void Main_Loop(void){

	ShaderSetup();

	GLFWwindow * wnd = glfwGetCurrentContext();

	Projection_Init(&Camera[0]);
	Projection_Init(&Camera[1]);

	GLSLProg_Init(&Program[0]);
	GLSLProg_Init(&Program[1]);
	Rectangle_Init(&Rect[0], 1.00f, 1.00f, 2.0f, 1.0f);		// size, X, Y location
	Rectangle_Init(&Rect[1], 0.02f, 0.02f, 1.0f, 1.0f);

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
	Program[1].Init( &Program[1], "GLSL/VShader2.glsl", "GLSL/FShader2.glsl");

	Program[0].LoadTexture( &Program[0], "data/skin2.tga", "tSampler", &Texture[0], 0);			// Location 0 = gl_Texture0 && Shader bound
	Program[1].LoadTexture( &Program[1], "data/font.tga", "tSampler", &Texture[1], 1);			// Location 0 = gl_Texture1 && Shader bound

	Program[0].CameraIndex = 0;																	// * NEW * point to Camera 0 (Frustum)
	Program[1].CameraIndex = 1;																	// * NEW * point to Camera 1 (Orthographic)

    float length    = 1.0 / 16;					// Texcoords
    int size        = 16 * 16 * 8; 				// 16 * 16 * 8

	float DataBlock[size];
	int counter     = 0;

    for(int i = 0; i < 16; i++){
        for(int n = 0; n < 16; n++){
			DataBlock[counter + 0] = n * length;         	// Corner 1
			DataBlock[counter + 1] = i * length;			
			DataBlock[counter + 2] = (n + 1) * length;   	// Corner 2
			DataBlock[counter + 3] = i * length;
			DataBlock[counter + 4] = (n + 1) * length;	 	// Corner 3
			DataBlock[counter + 5] = (i + 1) * length;
			DataBlock[counter + 6] = n * length;   			// Corner 4
			DataBlock[counter + 7] = (i + 1) * length;            
            counter += 8;
        }
    }

	const char msg[] = "Ahmad, Game dev? moeilijk no mpp!";
	int messageInt[64];

	StrtoArray( msg, messageInt, 64);

	Program[1].uBufferObject( &Program[1], sizeof(float[2048]), DataBlock, "Fontmap", GL_STATIC_DRAW);    			// this is setting the texcoord
	Program[1].uBufferObject( &Program[1], sizeof(int[64]), messageInt, "Message", GL_DYNAMIC_DRAW);

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

			int cam = Program[i].CameraIndex;

			Camera[cam].Lookup(&Camera[cam]);
			Program[i].EnableProgram(&Program[i]);
			
			MLoadIdentity( Proj_View);
			Camera[cam].GetProjView(&Camera[cam], Proj_View);
			Program[i].SetUniformMatrix(&Program[i], "uProjView", Proj_View);
			
			Program[i].EnableTexture(&Program[i], Texture[i], TEXTURE_MODE[i]);					// TEXTURE BINDING!!!
			// Rect[i].Render(&Rect[i], 0.0f, 0.0f);
			Rect[i].RenderInstances(&Rect[i], 0.0f, 0.0f, DrawInstance[i]);

			Program[i].DisableTexture(&Program[i]);
			Program[i].DisableProgram(&Program[i]);
		}

		glfwSwapBuffers(wnd);
		glfwPollEvents();
		CheckGLError();
	}
}

