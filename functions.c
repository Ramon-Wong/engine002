#include "functions.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


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

GLuint	vao;
GLuint	vbo;
GLuint	ebo;

void				Draw_Square(void);
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
	SetupVAOArray( &vao, &vbo, &ebo, vertices, colors, texCoords,
					indices,  sizeof(indices), 
					sizeof(vertices), sizeof(colors), sizeof(texCoords));


    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL error: %d\n", error);
		Shut_Down(1);
    }
	// texture setup

    int x,y,n;
    unsigned char * data = stbi_load("skin2.tga", &x, &y, &n, 0);

	GLuint 		m_texture;
	GLuint 		n_texture;
   
	GLuint		fbo;






	// creating FrameBuffer Object
	// CreateTexture( GL_TEXTURE_2D, &n_texture, NULL, x, y, GL_RGB);					// create an empty texture 

	// glGenFramebuffers(1, &fbo);
	// glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	// glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, n_texture, 0);

	// // // check if the fbo is complete
	// if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
    // 	// handle error
	// 	printf("\n Failed in creating Frame Buffer. \n");
	// }



    if (data == NULL) { 
		printf("\nCan't open tga file");
    } else {
		glBindTexture(GL_TEXTURE_2D, 0);                                    			// unBind your texture
		CreateTexture( GL_TEXTURE_2D, &m_texture, data, x, y, GL_RGBA);
		// glGenerateMipmap(GL_TEXTURE_2D);

		glUseProgram( GLSL_Program);                                                    // Use the shader program
		GLuint textureLocation = glGetUniformLocation(  GLSL_Program, "tSampler");
		
		// glActiveTexture(GL_TEXTURE0);                                                   // Assuming your texture is bound to GL_TEXTURE0    
		glBindTexture(GL_TEXTURE_2D, m_texture);                                    	// Bind your texture to GL_TEXTURE0    
		glUniform1i(textureLocation, 0);                                                // 0 corresponds to GL_TEXTURE0

		stbi_image_free(data);
		printf("\n texture Process %i/%i/%i \n", x, y, n);


		// created framebuffer for n_texture

		glBindTexture(GL_TEXTURE_2D, 0);                                    			// unBind your texture
		CreateTexture( GL_TEXTURE_2D, &n_texture, NULL, 512, 512, GL_RGB);

		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, n_texture, 0);

		// check if the fbo is complete
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
    	// handle error
			printf("\n Failed in creating Frame Buffer. \n");
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// end framebuffer
    }

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

		// glUseProgram( GLSL_Program);                                                    // Use the shader program
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLint rotat_zLocation = glGetUniformLocation( GLSL_Program, "rotate_z");
		glUniform1f( rotat_zLocation, rotate_z);	

		glUseProgram( GLSL_Program);		
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
	glDeleteTextures(1, &n_texture);

	glDeleteFramebuffers(1, &fbo);

	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

}




void Draw_Square(){
	glBindVertexArray(vao);
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
	Draw_Square();
}
