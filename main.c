#include "functions.h"

// http://www.songho.ca/opengl/gl_vbo.html#example1

    unsigned int		GLSL_Program;
    unsigned int		GLSL_vertex;
    unsigned int		GLSL_fragment;

    GLfloat				Proj_Matrix[16];
    GLfloat				View_Matrix[16];
    GLfloat				View_Proj[16];

    GLuint				uMatLoc[5];

int main(int argc, char *argv[]){

    GLfloat points[] = {
        0.0f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
       -0.5f, -0.5f,  0.0f
    };

    GLubyte indices[] = {
        0, 1, 2
    };    

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
	
		uMatLoc[0]	= glGetUniformLocation( GLSL_Program, "ViewProj_Matrix");
		glUniformMatrix4fv( uMatLoc[0], 1, GL_FALSE, View_Proj);	

		if(glfwGetKey( glfwGetCurrentContext(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			Shutdown(0);
		}

		// old way of drawing a triangle using system memory instead of VBO
		// this method sucks and is slow, but it works and is easy to understand
		glUseProgram(GLSL_Program);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, points);

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices);
	
		glDisableClientState(GL_VERTEX_ARRAY);


		glfwPollEvents();
		glfwSwapBuffers(glfwGetCurrentContext());
	}	



    Shutdown(0);
    return 0;
}

