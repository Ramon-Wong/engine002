#include "functions.h"




GLuint		GLSL_Program;
GLuint		GLSL_vertex;
GLuint		GLSL_fragment;

GLfloat		Proj_Matrix[16];
GLfloat		View_Matrix[16];


void Init(void){
    const int window_width = 800;
    const int window_height = 600;
 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  	GLFWwindow * window = glfwCreateWindow( window_width, window_height, "LearnOpenGL", NULL, NULL);
	if( !window ){
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
	
	//~ gluLookAt(0, 0, 12,     0, 0, 6,     0, 1, 0);
	
	LookAtM( View_Matrix, Pose, View, Upvx);	

	while(1){ 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		
		glfwSwapBuffers(window);
	}
 }


void Shutdown(int return_code){

	glfwTerminate();
	exit(return_code);
}
