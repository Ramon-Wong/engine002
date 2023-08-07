#include "functions.h"


float rotate_z = 0.0f;

const float rotations_per_tick = 0.2f;


GLfloat vertices[]	= {  4.0f, 4.0f, -14.0f, 
						-4.0f, 4.0f, -14.0f,
						-4.0f,-4.0f, -14.0f, 
						 4.0f,-4.0f, -14.0f};	
GLubyte indices[]	= {  0, 1, 2, 2, 3, 0}; 

GLuint	uMatLoc[5];



void Main_Loop(void){
	double old_time = glfwGetTime();
	
	while(1){
		double current_time = glfwGetTime();
		double delta_rotate = (current_time - old_time) * rotations_per_tick * 360;
		
		old_time = current_time;
		if(glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
		break;
				
		rotate_z += 0.65 * delta_rotate;
 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram( GLSL_Program);
		
		uMatLoc[0]	= glGetUniformLocation( GLSL_Program, "RED");
		glUniform1f( uMatLoc[0], 1.0f);
		
		uMatLoc[1]	= glGetUniformLocation( GLSL_Program, "PI");
		glUniform1f( uMatLoc[1], PI);
				
		uMatLoc[2]	= glGetUniformLocation( GLSL_Program, "rotate_z");
		glUniform1f( uMatLoc[2], rotate_z);		
				
		uMatLoc[3]	= glGetUniformLocation( GLSL_Program, "uView_Matrix");
		glUniformMatrix4fv( uMatLoc[3], 1, GL_FALSE, View_Matrix);
		
		uMatLoc[4]	= glGetUniformLocation( GLSL_Program, "uProj_Matrix");
		glUniformMatrix4fv( uMatLoc[4], 1, GL_FALSE, Proj_Matrix);		
		
		Draw();
		
		glfwSwapBuffers();
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
