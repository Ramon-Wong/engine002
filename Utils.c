#include "functions.h"



GLfloat		Proj_Matrix[16];
GLfloat		View_Matrix[16];

void Init(void){
	const int window_width = 800;
    const int window_height = 600;
 
	if( glfwInit() != GL_TRUE)
	Shut_Down(1);
  
	if( glfwOpenWindow(window_width, window_height, 5, 6, 5, 0, 0, 0, GLFW_WINDOW) != GL_TRUE)
		Shut_Down(1);
		
	glfwSetWindowTitle("The GLFW Window");
 
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
 }

void Shut_Down(int return_code){
	glDeleteProgram( GLSL_Program);
	glDeleteShader( GLSL_vertex);
	glDeleteShader( GLSL_fragment);		
	
	glfwTerminate();
	exit(return_code);
}


char *	ReadFile(const char * path){
	
	//~ usage										<==
	//~ 											<==
	//~ char * txt;									<==
	//~ 											<==	
	//~ txt = ReadFile("GLSL/loremipsum.txt");		<==
	//~ printf(" txt: %s", txt);					<==
	//~ free(txt);									<== memory leak
	//~ 											<==
	
	FILE *	tFile;
	char *	buffer;
	int		lSize;
	
	tFile = fopen( path, "rt");
	if(tFile){
		
		fseek( tFile, 0, SEEK_END);
		lSize = ftell( tFile);
		rewind( tFile);
		
		buffer = (char*) malloc( sizeof(char)*(lSize+1));
		fread( buffer, 1, lSize, tFile);
		buffer[lSize] = '\0';
		
		fclose(tFile);
	}else{
		printf("Error at opening file: %s", path);
	}
	
	return buffer;
}

