#include "functions.h"


float rotate_z = 0.0f;

const float rotations_per_tick = 0.2f;


GLfloat vertices[]	= {  4.0f, 4.0f, -14.0f, 
						-4.0f, 4.0f, -14.0f,
						-4.0f,-4.0f, -14.0f, 
						 4.0f,-4.0f, -14.0f};	
GLubyte indices[]	= {  0, 1, 2, 2, 3, 0}; 

GLfloat colors[]	= {  1.0f, 0.0f, 0.0f, 
						 0.0f, 1.0f, 0.0f,
						 0.0f, 0.0f, 1.0f, 
						 1.0f, 1.0f, 1.0f};	

GLuint	uMatLoc[6];
GLuint	bMatLoc[6];

GLFWwindow * wnd;

GLuint	vao;
GLuint	vbo;
GLuint	ebo;

void				Draw_Square(void);
void				Draw(void);


int					array[3][3] = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};

void				somethingsomething( int, int, int[][]);


void Main_Loop(void){

	somethingsomething( 3, 3, array);

	GLfloat		Proj_Matrix[16];
	GLfloat		View_Matrix[16];

	MLoadIdentity(Proj_Matrix);
	MLoadIdentity(View_Matrix); 
 
	float aspect_ratio = ((float)600) / 800;
	MFrustum( (float*)Proj_Matrix, 0.5f, -0.5f, -0.5f * aspect_ratio, 0.5f * aspect_ratio, 1.0f, 100.0f);	
	
	float View[] = {  0.0f,  0.0f, 12.0f};
	float Pose[] = {  0.0f,  0.0f,  6.0f};
	float Upvx[] = {  0.0f,  1.0f,  0.0f};
	
	LookAtM( View_Matrix, Pose, View, Upvx);

	GLfloat ProjView[16];
	MMultiply( ProjView, Proj_Matrix, View_Matrix);

	SetupVAO( &vao, &vbo, &ebo, vertices, colors, indices, sizeof(vertices), sizeof(colors), sizeof(indices));

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL error: %d\n", error);
		Shut_Down(1);
    }

	while(!glfwWindowShouldClose(wnd)){
		
		if(glfwGetKey( wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS){
			glfwSetWindowShouldClose( wnd, 1);
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram( GLSL_Program);		

		uMatLoc[3]	= glGetUniformLocation( GLSL_Program, "uProjView");
		glUniformMatrix4fv( uMatLoc[3], 1, GL_FALSE, ProjView);		
		
		Draw();

		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			fprintf(stderr, "OpenGL error in mainloop: %d\n", error);
			Shut_Down(1);
		}
		glfwSwapBuffers(wnd);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

}




void Draw_Square(){
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Draw your geometry
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}


void Draw(void){
	Draw_Square();
}

void somethingsomething( int x, int y, int array[x][y]){


}
