#include "functions.h"





void	print_shader_info_log(GLuint);
void	print_program_info_log(GLuint);







void	ShaderSetup(){
	if(glewInit() != GLEW_OK)
	printf("glewInit not supported");
	
	if(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader){
		printf("\n\nReady for GLSL \n\n");	
	}else{
		printf("\nNot totally ready for GLSL ;_; >> GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader ");
	}
	
	if(GLEW_ARB_vertex_program)											printf("Status: ARB vertex programs available.\n");
	if(glewGetExtension("GL_ARB_fragment_program"))						printf("Status: ARB fragment programs available.\n");
	if(glewIsSupported("GL_VERSION_1_4 GL_ARB_point_sprite"))			printf("Status: ARB point sprites available.\n");	
	printf("\n");	
	
		
	// GLSL_Program[1]		= glCreateProgram();
	// GLSL_vertex[1]		= ReadGLSLScript( GLSL_Program[1], 0, "GLSL/VShader2.glsl");
	// GLSL_fragment[1]	= ReadGLSLScript( GLSL_Program[1], 1, "GLSL/FShader2.glsl");
	// LinkPrograms(GLSL_Program[1]);
	
}







void	print_shader_info_log(GLuint shader_index){
	int max_length = 2048;
	int actual_length = 0;
	char log[2048];
	glGetShaderInfoLog (shader_index, max_length, &actual_length, log);
	printf ("shader info log for GL index %u:\n%s\n", shader_index, log);
}


void	print_program_info_log(GLuint programme) {
	int max_length = 2048;
	int actual_length = 0;
	char log[2048];
	glGetProgramInfoLog (programme, max_length, &actual_length, log);
	printf ("program info log for GL index %u:\n%s", programme, log);
}


GLuint	ReadGLSLScript(GLuint Prog, unsigned int I, const char * path){
	//~ case of I parameter
	//~ 0 = GL_VERTEX_SHADER
	//~ 1 = GL_FRAGMENT_SHADER
	
	GLuint glsl;
	int params;	
	char * vv	= ReadFile(path);
		
	printf("Compiling Shader: %s\n", path);
	
	if( I == 0){
		glsl		= glCreateShader(GL_VERTEX_SHADER);
	}else if( I == 1){
		glsl		= glCreateShader(GL_FRAGMENT_SHADER);
	}
	
	glShaderSource( glsl, 1, (const GLchar **)&vv, 0);
	glCompileShader(glsl);
		
	params	= -1;
	glGetShaderiv(glsl, GL_COMPILE_STATUS, &params);	

		
	if(GL_TRUE != params) {
		printf("Error Compiling: %s\n", path);
		print_shader_info_log(glsl);
	}
		
	glAttachShader( Prog, glsl);	
	free(vv);

	return glsl;
}


void	LinkPrograms(GLuint glsl_program){
	
	GLint prog_link_success;
	
	glLinkProgram( glsl_program);
	glGetObjectParameterivARB( glsl_program, GL_OBJECT_LINK_STATUS_ARB, &prog_link_success);
	
	if(!prog_link_success){
		printf("\nThe shaders could not be linked\n");
		print_program_info_log(glsl_program);
	}else{
		printf("\nShaders Succesfully Created And Linked\n");
	}
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