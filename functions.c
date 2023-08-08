#include "functions.h"


GLuint		GLSL_Program;
GLuint		GLSL_vertex;
GLuint		GLSL_fragment;

GLfloat		Proj_Matrix[16];
GLfloat		View_Matrix[16];


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

	while(1){
		// double current_time = glfwGetTime();
		// double delta_rotate = (current_time - old_time) * rotations_per_tick * 360;
		
		// old_time = current_time;

    	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			Shutdown(0);
    	}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// glUseProgram( GLSL_Program);
		
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}	
 }


 void Shutdown(int return_code){
    
	glfwTerminate();
	exit(return_code);
}
