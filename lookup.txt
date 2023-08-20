#include "functions.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float rotate_z = 0.0f;

const float rotations_per_tick = 0.2f;


GLfloat vertices[]	= {  4.0f, 4.0f, -14.0f, 
						-4.0f, 4.0f, -14.0f,
						-4.0f,-4.0f, -14.0f, 
						 4.0f,-4.0f, -14.0f};	
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
	double old_time = glfwGetTime();

	GLfloat		Proj_Matrix[16];
	GLfloat		View_Matrix[16];
	GLuint 		m_texture;

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


    int x,y,n;
    unsigned char * data = stbi_load("skin2.tga", &x, &y, &n, 0);
    if (data == NULL) {
		printf("\nCan't open tga file");
    } else {

		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data); 
 		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);



		printf("\n texture Process %i/%i/%i \n", x, y, n);
    }
    stbi_image_free(data);

    


	while(!glfwWindowShouldClose(wnd)){
		double current_time = glfwGetTime();
		double delta_rotate = (current_time - old_time) * rotations_per_tick * 360;
		

		if(glfwGetKey( wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS){
			glfwSetWindowShouldClose( wnd, 1);
		}
				
		rotate_z = 0.1 * delta_rotate;
 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram( GLSL_Program);
		
		uMatLoc[0]	= glGetUniformLocation( GLSL_Program, "RED");
		glUniform1f( uMatLoc[0], 1.0f);
		
		uMatLoc[1]	= glGetUniformLocation( GLSL_Program, "PI");
		glUniform1f( uMatLoc[1], PI);
				
		uMatLoc[2]	= glGetUniformLocation( GLSL_Program, "rotate_z");
		glUniform1f( uMatLoc[2], rotate_z);		

		uMatLoc[3]	= glGetUniformLocation( GLSL_Program, "uProjView");
		glUniformMatrix4fv( uMatLoc[3], 1, GL_FALSE, ProjView);		

		glActiveTexture(GL_TEXTURE0);  // Use texture unit 0
		glBindTexture(GL_TEXTURE_2D, m_texture);  // Bind your texture here

		// Set the "u_texture" uniform in the shader to use texture unit 0
		GLint textureUniform = glGetUniformLocation( GLSL_Program, "u_texture");
		if (textureUniform != -1) {
    		glUniform1i(textureUniform, 0);  // 0 corresponds to texture unit 0
		}

		Draw();
				
		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);

		glfwSwapBuffers(wnd);
		glfwPollEvents();
	}

	glDeleteTextures(1, &m_texture);
}




void Draw_Square(){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

 

void Draw(void){
	Draw_Square();
}
