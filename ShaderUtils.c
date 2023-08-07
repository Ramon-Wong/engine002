#include "functions.h"


GLuint	GLSL_Program;
GLuint	GLSL_vertex;
GLuint	GLSL_fragment;


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
	
	GLSL_Program	= glCreateProgram();
	GLSL_vertex		= glCreateShader(GL_VERTEX_SHADER);
	GLSL_fragment	= glCreateShader(GL_FRAGMENT_SHADER);


	int params;	
	char * vv	= ReadFile("GLSL/VShader.glsl");
	printf("Compiling Shader: GLSL/VShader.glsl\n");
	
	glShaderSource( GLSL_vertex, 1, (const GLchar **)&vv, 0);
	glCompileShader(GLSL_vertex);
	params	= -1;
	glGetShaderiv (GLSL_vertex, GL_COMPILE_STATUS, &params);	
	if(GL_TRUE != params) {
		printf("Error Compiling: GLSL/vShader.glsl\n");
		print_shader_info_log(GLSL_vertex);
	}
	glAttachShader(GLSL_Program, GLSL_vertex);	
	free(vv);


	char * fv	= ReadFile("GLSL/FShader.glsl");
	printf("Compiling Shader: GLSL/FShader.glsl\n");
	
	glShaderSource( GLSL_fragment, 1, (const GLchar **)&fv, 0);
	glCompileShader(GLSL_fragment);
	params	= -1;
	glGetShaderiv (GLSL_fragment, GL_COMPILE_STATUS, &params);	
	if(GL_TRUE != params) {
		printf("Error Compiling: glsl/fShader.glsl\n");
		print_shader_info_log(GLSL_fragment);
	}	
	glAttachShader(GLSL_Program, GLSL_fragment);	
	free(fv);

	
	glLinkProgram(GLSL_Program);
	GLint prog_link_success;
	glGetObjectParameterivARB( GLSL_Program, GL_OBJECT_LINK_STATUS_ARB, &prog_link_success);
	
	if(!prog_link_success){
		printf("\nThe shaders could not be linked\n");
		print_program_info_log(GLSL_Program);
	}else{
		printf("\nShaders Succesfully Created And Linked\n");
	}
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
