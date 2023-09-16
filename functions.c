#include "functions.h"

// #define STB_IMAGE_IMPLEMENTATION
// #include <stb/stb_image.h>


const float rotations_per_tick		= 0.2f;
	  float rotate_z				= 0.0f;


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


GLFWwindow * wnd;

GLuint				GLSL_Program;
GLuint				GLSL_vertex;
GLuint				GLSL_fragment;

GLuint	VAO[3];						// Vertice Array Object holding ya, array object, buffer objects.
GLuint	BOX[3];						// BOX

void				Draw_Square(GLuint);
void				Draw(void);


void Main_Loop(void){
	double old_time = glfwGetTime();

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

	// SetupVAO( &vao, &vbo, &ebo, vertices, colors, indices, sizeof(vertices), sizeof(colors), sizeof(indices));
	SetupVAOArray( &VAO[0], &VAO[1], &VAO[2], vertices, colors, texCoords,
					indices,  sizeof(indices), 
					sizeof(vertices), sizeof(colors), sizeof(texCoords));

	SetupVAOArray( &BOX[0], &BOX[1], &BOX[2], box_vertices, box_normals, box_colors,
					box_indices,  sizeof(box_indices), 
					sizeof(box_vertices), sizeof(box_normals), sizeof(box_colors));



    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL error: %d\n", error);
		Shut_Down(1);
    }
	// texture setup

	GLuint 		m_texture = LoadTexture( GLSL_Program, "data/skin2.tga", "tSampler", 0);   

	// projection matrix outside the rendering loop
	GLuint ProjLocation		= glGetUniformLocation( GLSL_Program, "uProjView");
	glUniformMatrix4fv( ProjLocation, 1, GL_FALSE, ProjView);		

	// texture setup end

	while(!glfwWindowShouldClose(wnd)){

		double current_time = glfwGetTime();
		double delta_rotate = (current_time - old_time) * rotations_per_tick * 360;

		rotate_z = 0.1 * delta_rotate;

		if(glfwGetKey( wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS){
			glfwSetWindowShouldClose( wnd, 1);
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLint rotat_zLocation = glGetUniformLocation( GLSL_Program, "rotate_z");
		glUniform1f( rotat_zLocation, rotate_z);	

		glUseProgram( GLSL_Program);		
		
   		glActiveTexture(GL_TEXTURE0);		
		glBindTexture(GL_TEXTURE_2D, m_texture);

		Draw();

		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			fprintf(stderr, "OpenGL error in mainloop: %d\n", error);
			Shut_Down(1);
		}
		glfwSwapBuffers(wnd);
		glfwPollEvents();
	}

	glDeleteTextures(1, &m_texture);

	glDeleteBuffers(1, &VAO[2]);
	glDeleteBuffers(1, &VAO[1]);
	glDeleteVertexArrays(1, &VAO[0]);

	glDeleteBuffers(1, &BOX[2]);
	glDeleteBuffers(1, &BOX[1]);
	glDeleteVertexArrays(1, &BOX[0]);
}




void Draw_Square( GLuint array_buffer){
	glBindVertexArray( array_buffer);
	glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
    // Draw your geometry
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}


void Draw(void){
	Draw_Square(VAO[0]);
}
