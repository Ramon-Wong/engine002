#include "functions.h"


float rotate_z = 0.0f;

const float rotations_per_tick = 0.2f;


GLfloat vertices[]	= {  4.0f, 4.0f, -14.0f,	-4.0f, 4.0f, -14.0f,	-4.0f,-4.0f, -14.0f,	 4.0f,-4.0f, -14.0f};
GLfloat Colors[]	= {  1.0f, 1.0f,   1.0f,	 1.0f, 1.0f,   1.0f,	 1.0f, 1.0f,   1.0f,	 1.0f, 1.0f,   1.0f};
GLfloat TexCoord[]	= {  0.0f, 0.0f,			 0.0f, 0.0f,			 0.0f, 0.0f,			 0.0f, 0.0f};

GLubyte indices[]	= {  0, 1, 2, 2, 3, 0}; 


GLuint GLSL_Prog[3];




void glCheckError(){
	GLenum error = glGetError();
	while(error){
		fprintf("Opengl Error code: %d\n", error);
	}
}


void Shut_Down(int return_code){
	
		
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
	GLfloat		Proj_View[16];

	MLoadIdentity(Proj_Matrix);
	MLoadIdentity(View_Matrix);
 	MLoadIdentity(Proj_View);

	float View[] = {  0.0f,  0.0f, 12.0f};
	float Pose[] = {  0.0f,  0.0f,  6.0f};
	float Upvx[] = {  0.0f,  1.0f,  0.0f};
	
	LookAtM( View_Matrix, Pose, View, Upvx);
	MMultiply( Proj_View, Proj_Matrix, View_Matrix);
	float aspect_ratio = ((float)600) / 800;
	MFrustum( (float*)Proj_Matrix, 0.5f, -0.5f, -0.5f * aspect_ratio, 0.5f * aspect_ratio, 1.0f, 100.0f);	


	while(!glfwWindowShouldClose(wnd)){
		double current_time = glfwGetTime();
		double delta_rotate = (current_time - old_time) * rotations_per_tick * 360;

		if(glfwGetKey( wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS){
			glfwSetWindowShouldClose( wnd, 1);
		}

		rotate_z = 0.1 * delta_rotate;
 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glCheckError();

		glUseProgram( GLSL_Prog[0]);
		
		glUniform1f( glGetUniformLocation( GLSL_Prog[0], "RED"),			1.0f);
		glUniform1f( glGetUniformLocation( GLSL_Prog[0], "PI"),				PI);
		glUniform1f( glGetUniformLocation( GLSL_Prog[0], "rotate_z"),		rotate_z);
		glUniformMatrix4fv( glGetUniformLocation( GLSL_Prog[0], "uProjView"), 		1, GL_FALSE, Proj_View);
		
		Draw();
				
		glfwSwapBuffers(wnd);
		glfwPollEvents();
	}
}




void Draw_Square(){
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
	
	glDisableClientState(GL_VERTEX_ARRAY); // disable vertex arrays
}

 

void Draw(void){
	Draw_Square();
}
