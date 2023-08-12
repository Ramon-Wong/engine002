#include "functions.h"


GLuint		GLSL_Program;
GLuint		GLSL_vertex;
GLuint		GLSL_fragment;

GLfloat		Proj_Matrix[16];
GLfloat		View_Matrix[16];

float rotate_z = 0.0f;
const float rotations_per_tick = 0.2f;

// GLfloat vertices[]	= {  4.0f, 4.0f, -14.0f, 
// 						-4.0f, 4.0f, -14.0f,
// 						-4.0f,-4.0f, -14.0f, 
// 						 4.0f,-4.0f, -14.0f};	
// GLubyte indices[]	= {  0, 1, 2, 2, 3, 0}; 

GLuint		uMatLoc[5];

void Init(void){
	const int window_width  = 800;
    const int window_height = 600;
 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow * window = glfwCreateWindow( window_width, window_height, "Hello GLFW", NULL, NULL);
    if (!window) {
        Shutdown(1);
    }
	
 	glfwMakeContextCurrent(window);		
     
 
	printf("GL VENDOR:--- %s \n", glGetString(GL_VENDOR));
	printf("GL RENDERER:- %s \n", glGetString(GL_RENDERER));
	printf("GL VERSION:-- %s \n", glGetString(GL_VERSION));
	printf("GL SHADING:-- %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
 

 	MLoadIdentity(Proj_Matrix);
	MLoadIdentity(View_Matrix); 
 
	float aspect_ratio = ((float)window_height) / window_width;
	MFrustum( (float*)Proj_Matrix, 0.5f, -0.5f, -0.5f * aspect_ratio, 0.5f * aspect_ratio, 1.0f, 100.0f);	
	
	float View[] = {  0.0f,  0.0f, 12.0f};
	float Pose[] = {  0.0f,  0.0f,  6.0f};
	float Upvx[] = {  0.0f,  1.0f,  0.0f};
	
	LookAtM( View_Matrix, Pose, View, Upvx);

	ShaderSetup();

	double old_time = glfwGetTime();

	while(1){
		double current_time = glfwGetTime();
		double delta_rotate = (current_time - old_time) * rotations_per_tick * 360;
		
		old_time = current_time;

    	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			Shutdown(0);
    	}

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
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}	
 }


 void Shutdown(int return_code){
    
	glfwTerminate();
	exit(return_code);
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