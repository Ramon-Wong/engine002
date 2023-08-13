#include "functions.h"


float rotate_z = 0.0f;

const float rotations_per_tick = 0.2f;


GLfloat vertices[]	= {  4.0f, 4.0f, -14.0f, 
						-4.0f, 4.0f, -14.0f,
						-4.0f,-4.0f, -14.0f, 
						 4.0f,-4.0f, -14.0f};	
GLubyte indices[]	= {  0, 1, 2, 2, 3, 0}; 

GLuint	uMatLoc[6];
GLuint	bMatLoc[6];

GLFWwindow * wnd;

void Draw3DSGrid(){
	glColor3ub(0, 255, 0);
	// Draw a 1x1 grid along the X and Z axis'
	int i;
	
	for(i = -50; i <= 50; i += 1){
		glBegin(GL_LINES);
			glVertex3f(-50, -1,  i);
			glVertex3f( 50, -1,  i);
			glVertex3f(  i, -1, -50);
			glVertex3f(  i, -1,  50);
		glEnd();
	}
}




void Main_Loop(void){
	double old_time = glfwGetTime();
	
	while(!glfwWindowShouldClose(wnd)){
		double current_time = glfwGetTime();
		double delta_rotate = (current_time - old_time) * rotations_per_tick * 360;
		


		if(glfwGetKey( wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS){
			glfwSetWindowShouldClose( wnd, 1);
		}
				
		rotate_z = 0.1 * delta_rotate;
 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		GLfloat ProjView[16];
		MMultiply( ProjView, Proj_Matrix, View_Matrix);
		
		glUseProgram(GLSL_Program[1]);
		bMatLoc[0]	= glGetUniformLocation( GLSL_Program[1], "uView_Matrix");
		glUniformMatrix4fv( bMatLoc[0], 1, GL_FALSE, View_Matrix);
		
		bMatLoc[1]	= glGetUniformLocation( GLSL_Program[1], "uProj_Matrix");
		glUniformMatrix4fv( bMatLoc[1], 1, GL_FALSE, Proj_Matrix);		
		
		bMatLoc[2]	= glGetUniformLocation( GLSL_Program[1], "uProjView");
		glUniformMatrix4fv( bMatLoc[2], 1, GL_FALSE, ProjView);			
		Draw3DSGrid();	
		
		
		glUseProgram( GLSL_Program[0]);
		
		uMatLoc[0]	= glGetUniformLocation( GLSL_Program[0], "RED");
		glUniform1f( uMatLoc[0], 1.0f);
		
		uMatLoc[1]	= glGetUniformLocation( GLSL_Program[0], "PI");
		glUniform1f( uMatLoc[1], PI);
				
		uMatLoc[2]	= glGetUniformLocation( GLSL_Program[0], "rotate_z");
		glUniform1f( uMatLoc[2], rotate_z);		
				
		uMatLoc[3]	= glGetUniformLocation( GLSL_Program[0], "uView_Matrix");
		glUniformMatrix4fv( uMatLoc[3], 1, GL_FALSE, View_Matrix);
		
		uMatLoc[4]	= glGetUniformLocation( GLSL_Program[0], "uProj_Matrix");
		glUniformMatrix4fv( uMatLoc[4], 1, GL_FALSE, Proj_Matrix);		
		
		uMatLoc[5]	= glGetUniformLocation( GLSL_Program[0], "uProjView");
		glUniformMatrix4fv( uMatLoc[5], 1, GL_FALSE, ProjView);		
		
		
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
