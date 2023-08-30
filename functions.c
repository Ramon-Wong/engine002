#include "functions.h"


float rotate_z = 0.0f;

const float rotations_per_tick = 0.2f;



GLfloat Vertices[]	= {  4.0f, 4.0f, -14.0f,
						-4.0f, 4.0f, -14.0f,
						-4.0f,-4.0f, -14.0f,
						 4.0f,-4.0f, -14.0f};

GLfloat Colors[] = {	1.0f, 1.0f, 1.0f,	// Red
    					1.0f, 1.0f, 1.0f,	// Green
    					1.0f, 1.0f, 1.0f,	// Blue
    					1.0f, 1.0f, 1.0f};	// White


GLubyte indices[]	= {  0, 1, 2, 2, 3, 0}; 

GLfloat texCoords[] = {	1.0f, 1.0f,   // Top-right
						0.0f, 1.0f,   // Top-left
    					0.0f, 0.0f,   // Bottom-left
    					1.0f, 0.0f }; // Bottom-right

GLuint	uMatLoc[6];
GLuint	bMatLoc[6];

GLFWwindow * wnd;



void				Draw_Square(void);
void				Draw(void);


void Main_Loop(void){
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


    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL error at start: %d\n", error);
		Shut_Down(1);
    }

	while(!glfwWindowShouldClose(wnd)){

		if(glfwGetKey( wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS){
			glfwSetWindowShouldClose( wnd, 1);
		}
				 
		// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// glUseProgram( GLSL_Program);
		
		// uMatLoc[3]	= glGetUniformLocation( GLSL_Program, "uProjView");
		// glUniformMatrix4fv( uMatLoc[3], 1, GL_FALSE, ProjView);		
		
		// Draw();

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            fprintf(stderr, "OpenGL error: %d\n", error);
			Shut_Down(1);
        }


		glfwSwapBuffers(wnd);
		glfwPollEvents();
	}
}




void Draw_Square(){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, Vertices);
    glColorPointer(3, GL_FLOAT, 0, Colors);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
	
	glDisableClientState(GL_VERTEX_ARRAY); // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY); 
}

 

void Draw(void){
	Draw_Square();
}
