#include "functions.h"




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


GLuint				GLSL_Prog[3];				// GLSL Program
GLuint				VAO[3];						// Vertice Array Object holding ya, array object, buffer objects.




void Draw_Object( GLuint, int);


void Shutdown(void){

	glDeleteBuffers(1, &VAO[2]);
	glDeleteBuffers(1, &VAO[1]);
	glDeleteVertexArrays(1, &VAO[0]);

	if( GLSL_Prog[0]){
		glDeleteProgram( GLSL_Prog[0]);
		glDeleteShader( GLSL_Prog[1]);
		glDeleteShader( GLSL_Prog[2]);		
	}	

    glfwTerminate();
}


void Mainloop(void){

	double old_time = glfwGetTime();

	GLfloat		Proj_Matrix[16];
	GLfloat		View_Matrix[16];
	GLfloat		Proj_View[16];

	MLoadIdentity(Proj_Matrix);
	MLoadIdentity(View_Matrix); 
	MLoadIdentity(Proj_View); 

	double rotate_z;
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

	SetupVAOArray( &VAO[0], &VAO[1], &VAO[2], vertices, colors, texCoords,
					indices,  sizeof(indices), 
					sizeof(vertices), sizeof(colors), sizeof(texCoords));

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL error: %d\n", error);
		Shutdown();
    }

	glUniformMatrix4fv( glGetUniformLocation( GLSL_Prog[0], "uProjView"),	1,	GL_FALSE, Proj_View);


	glEnable(GL_DEPTH_TEST);                                  // enable depth-testing
	glDepthFunc(GL_LESS);                                     // depth-testing interprets a smaller value as "closer"
	glViewport( 0, 0, Screen_width, Screen_height);

    GLFWwindow * wnd = glfwGetCurrentContext();

	while(!glfwWindowShouldClose(wnd)) {                      // Render the game until the user closes the window.
		double current_time = glfwGetTime();
		double delta_rotate = (current_time - old_time) * 0.2f * 360;

		rotate_z = 0.1 * delta_rotate;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // wipe the drawing surface clear
      // Break the while loop when the user presses the Escape key.
		if (glfwGetKey(wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS) { break;}

		glUniform1f( glGetUniformLocation( GLSL_Prog[0], "rotate_z"), rotate_z);
		glUniform1f( glGetUniformLocation( GLSL_Prog[0], "PI"), PI);

		Draw_Object( VAO[0], 6);	
      
		glfwPollEvents();                                       // Poll events to check for user input.
		glfwSwapBuffers(wnd);                                   // Swap buffers to display the rendered image.
	}	

    Shutdown();
}


void Draw_Object( GLuint array_buffer, int size){
	glBindVertexArray( array_buffer);
	glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
    // Draw your geometry
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_BYTE, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}