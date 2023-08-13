#include "functions.h"



void Init(void){
 
	if( glfwInit() != GL_TRUE)
	Shut_Down(1);
  
	wnd = glfwCreateWindow( 800, 600, "Hello Triangle", NULL, NULL);

	if(!wnd) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
	
	}

	glfwMakeContextCurrent(wnd);
 
	printf("GL VENDOR:--- %s \n", glGetString(GL_VENDOR));
	printf("GL RENDERER:- %s \n", glGetString(GL_RENDERER));
	printf("GL VERSION:-- %s \n", glGetString(GL_VERSION));
	printf("GL SHADING:-- %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
 
	int i;
	for(i = 0; i < MAX_SCRIPTS; i++){
		GLSL_Program[i]		= 0;
		GLSL_fragment[i]	= 0;
		GLSL_vertex[i]		= 0;	
	}

 }

void Shut_Down(int return_code){
	
	int i;
	for(i = 0; i < MAX_SCRIPTS; i++){
		
		if( GLSL_Program[i]){
			glDeleteProgram( GLSL_Program[i]);
			glDeleteShader( GLSL_vertex[i]);
			glDeleteShader( GLSL_fragment[i]);		
		}
	}
	
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

