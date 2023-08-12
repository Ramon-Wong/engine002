#include "functions.h"

// http://www.songho.ca/opengl/gl_vbo.html#example1

    unsigned int		GLSL_Program;
    unsigned int		GLSL_vertex;
    unsigned int		GLSL_fragment;

    GLfloat				Proj_Matrix[16];
    GLfloat				View_Matrix[16];
    GLfloat				View_Proj[16];

    GLuint				uMatLoc[5];



	GLfloat vertices[]	= {  4.0f, 4.0f, -14.0f, 
							-4.0f, 4.0f, -14.0f,
							-4.0f,-4.0f, -14.0f, 
							 4.0f,-4.0f, -14.0f};	

	GLubyte indices[]	= {  0, 1, 2, 2, 3, 0}; 

void Draw_Square();

int main(int argc, char *argv[]){

	const int window_width  = 800;
    const int window_height = 600;

    printf("Hello World!\n");
    Init( window_width, window_height, "prototype GLFW window");
	ShaderSetup("vshader.glsl", "fshader.glsl", &GLSL_Program, GLSL_vertex, GLSL_fragment);

	MLoadIdentity(View_Matrix);
	MLoadIdentity(Proj_Matrix);
	MLoadIdentity(View_Proj);

	float aspect_ratio = ((float)window_height) / window_width;
	MFrustum( (float*)Proj_Matrix, 0.35f, -0.35f, -0.5f * aspect_ratio, 0.5f * aspect_ratio, 1.0f, 100.0f);	

	float View[] = {  0.0f,  0.0f, 12.0f};
	float Pose[] = {  0.0f,  0.0f,  6.0f};
	float Upvx[] = {  0.0f,  1.0f,  0.0f};
		
	LookAtM( View_Matrix, Pose, View, Upvx);

	MMultiply(View_Proj, Proj_Matrix, View_Matrix);


	while(!glfwWindowShouldClose(glfwGetCurrentContext())) {
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		if(glfwGetKey( glfwGetCurrentContext(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			Shutdown(0);
		}

		glUseProgram(GLSL_Program);

		uMatLoc[0]	= glGetUniformLocation( GLSL_Program, "ViewProj_Matrix");
		glUniformMatrix4fv( uMatLoc[0], 1, GL_FALSE, View_Proj);	


		Draw_Square();


		glfwPollEvents();
		glfwSwapBuffers(glfwGetCurrentContext());
	}	



    Shutdown(0);
    return 0;
}



void Draw_Square(){
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
	
	glDisableClientState(GL_VERTEX_ARRAY); // disable vertex arrays
}
