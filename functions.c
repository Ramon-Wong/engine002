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
	// texture setup

    // int x,y,n;
    // unsigned char * data = stbi_load("skin2.tga", &x, &y, &n, 0);

	// GLuint 		m_texture;
   
    // if (data == NULL) { 
	// 	printf("\nCan't open tga file");
    // } else {

	// 	glGenTextures(1, &m_texture);
	// 	glActiveTexture(GL_TEXTURE0);
	// 	glBindTexture(GL_TEXTURE_2D, m_texture);

	// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 	if(n == 3) 
	// 		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0,  GL_RGB,	GL_UNSIGNED_BYTE, data);
	// 	else if (n == 4) 
	// 		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA,	GL_UNSIGNED_BYTE, data);
	// 	glGenerateMipmap(GL_TEXTURE_2D);

	// 	stbi_image_free(data);

	// 	printf("\n texture Process %i/%i/%i \n", x, y, n);

    // }
    
    // GLuint textureLocation = glGetUniformLocation(shaderProgram, "textureSampler");
    // glUseProgram(shaderProgram);                                                    // Use the shader program

    // glActiveTexture(GL_TEXTURE0);                                                   // Assuming your texture is bound to GL_TEXTURE0    
    // glBindTexture(GL_TEXTURE_2D, yourTextureID);                                    // Bind your texture to GL_TEXTURE0    
    // glUniform1i(textureLocation, 0);                                                // 0 corresponds to GL_TEXTURE0

	// texture setup end

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

	glDeleteTextures(1, &m_texture);

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
