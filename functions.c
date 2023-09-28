#include "functions.h"



GLuint	GLSL_Prog[3];				// GLSL Program


void Shutdown(void){

	if( GLSL_Prog[0]){
		glDeleteProgram( GLSL_Prog[0]);
		glDeleteShader( GLSL_Prog[1]);
		glDeleteShader( GLSL_Prog[2]);		
	}	

    glfwTerminate();
}


void Mainloop(void){

	GLfloat		Proj_Matrix[16];
	GLfloat		View_Matrix[16];
	GLfloat		Proj_View[16];

	MLoadIdentity(Proj_Matrix);
	MLoadIdentity(View_Matrix); 
	MLoadIdentity(Proj_View); 

	float View[] = {  0.0f,  0.0f, 12.0f};
	float Pose[] = {  0.0f,  0.0f,  6.0f};
	float Upvx[] = {  0.0f,  1.0f,  0.0f};

	float aspect_ratio = ((float)600) / 800;
	MFrustum( (float*)Proj_Matrix, 0.5f, -0.5f, -0.5f * aspect_ratio, 0.5f * aspect_ratio, 1.0f, 1000.0f);		
	LookAtM( View_Matrix, Pose, View, Upvx);	
	MMultiply( Proj_View, Proj_Matrix, View_Matrix);

	ShaderSetup1();
	GLSL_Prog[0]		= glCreateProgram();
	GLSL_Prog[1]		= ReadGLSLScript( GLSL_Prog[0], 0, "GLSL/VShader.glsl");
	GLSL_Prog[2]		= ReadGLSLScript( GLSL_Prog[0], 1, "GLSL/FShader.glsl");
	LinkPrograms(GLSL_Prog[0]);

	glEnable(GL_DEPTH_TEST);                                  // enable depth-testing
	glDepthFunc(GL_LESS);                                     // depth-testing interprets a smaller value as "closer"
	glViewport( 0, 0, Screen_width, Screen_height);

    GLFWwindow * wnd = glfwGetCurrentContext();

	while(!glfwWindowShouldClose(wnd)) {                      // Render the game until the user closes the window.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // wipe the drawing surface clear
      // Break the while loop when the user presses the Escape key.
		if (glfwGetKey(wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS) { break;}


      
		glfwPollEvents();                                       // Poll events to check for user input.
		glfwSwapBuffers(wnd);                                   // Swap buffers to display the rendered image.
	}	

    Shutdown();
}
