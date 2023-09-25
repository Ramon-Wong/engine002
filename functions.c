#include "functions.h"


const float rotations_per_tick		= 0.2f;
	  float timer					= 0.0f;


GLFWwindow * wnd;

GLuint				VAO[3];						// Vertice Array Object holding ya, array object, buffer objects.
GLuint				VBO[3];
GLuint				GLSL_Prog[3];				// GLSL Program

float				rot = 0.0f;

float				BOXX[] = { 12.5f,-10.0f,-7.5f,-5.0f,-2.5f, 2.5f, 5.0f, 7.5f, 10.0f, 12.5f};


void Main_Loop(void){
	double old_time = glfwGetTime();

	GLfloat		Proj_Matrix[16];
	GLfloat		View_Matrix[16];
	GLfloat		ProjView[16];

	MLoadIdentity(Proj_Matrix); 
	MLoadIdentity(View_Matrix); 

	GLSL_Prog[0]		= glCreateProgram();
	GLSL_Prog[1]		= ReadGLSLScript( GLSL_Prog[0], 0, "GLSL/vbShader.glsl");
	GLSL_Prog[2]		= ReadGLSLScript( GLSL_Prog[0], 1, "GLSL/fbShader.glsl");
	LinkPrograms(GLSL_Prog[0]);

	float aspect_ratio = ((float)600) / 800;
	MFrustum( (float*)Proj_Matrix, 0.5f, -0.5f, -0.5f * aspect_ratio, 0.5f * aspect_ratio, 1.0f, 100.0f);	
	
	float View[] = {  0.01f,  0.01f, 4.00f};
	float Pose[] = {  0.01f,  0.01f, 8.00f};
	float Upvx[] = {  0.01f,  1.00f, 0.01f};
	


	// // SetupVAO( &vao, &vbo, &ebo, vertices, colors, indices, sizeof(vertices), sizeof(colors), sizeof(indices));
	// SetupVAOArray( &VAO[0], &VAO[1], &VAO[2], vertices, colors, texCoords,
	// 				indices,  sizeof(indices), 
	// 				sizeof(vertices), sizeof(colors), sizeof(texCoords));

	SetupVAOArray( &VBO[0], &VBO[1], &VBO[2], box_vertices, box_normals, box_texcoords,
					box_indices,  sizeof(box_indices), 
					sizeof(box_vertices), sizeof(box_normals), sizeof(box_texcoords));

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL error: %d\n", error);
		Shut_Down(1);
    }
	// texture setup

	GLuint 		m_texture = LoadTexture( GLSL_Prog[0], "data/skin2.tga", "tSampler", 0);   

	LookAtM( View_Matrix, Pose, View, Upvx);
	MMultiply( ProjView, Proj_Matrix, View_Matrix);

	glUniformMatrix4fv( glGetUniformLocation( GLSL_Prog[0], "uProjView"),			1,	GL_FALSE, ProjView);
	// texture setup end

	glEnable(GL_DEPTH_TEST);  
	glFrontFace(GL_CCW);
	int FPS		= 0;

	while(!glfwWindowShouldClose(wnd)){

		LookAtM( View_Matrix, Pose, View, Upvx);

		MMultiply( ProjView, Proj_Matrix, View_Matrix);
		setPlanes( ProjView);

		glUniformMatrix4fv( glGetUniformLocation( GLSL_Prog[0], "uProjView"),			1,	GL_FALSE, ProjView);

		double current_time = glfwGetTime();
		double delta		= (current_time - old_time) * rotations_per_tick * 360;

		timer = 0.1 * delta;
		rot += 0.005f;
		FPS++;

		if( current_time - old_time >= 1.0){
			// printf("\n FPS: %i", FPS);						
			// FPS			= 0;
			// old_time	= current_time;
		}
		
		if(glfwGetKey( wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS){	glfwSetWindowShouldClose( wnd, 1);}
		if(glfwGetKey( wnd, GLFW_KEY_W) == GLFW_PRESS){			MoveCamera( Pose, View,-0.001f);}
		if(glfwGetKey( wnd, GLFW_KEY_S) == GLFW_PRESS){			MoveCamera( Pose, View, 0.001f);}
		if(glfwGetKey( wnd, GLFW_KEY_A) == GLFW_PRESS){			RotateCamera( Pose, View,-0.001f, 0.0f, 1.0f, 0.0f);}
		if(glfwGetKey( wnd, GLFW_KEY_D) == GLFW_PRESS){			RotateCamera( Pose, View, 0.001f, 0.0f, 1.0f, 0.0f);}
		if(glfwGetKey( wnd, GLFW_KEY_Q) == GLFW_PRESS){			StrafeCamera( Pose, View, 0.005f);}
		if(glfwGetKey( wnd, GLFW_KEY_E) == GLFW_PRESS){			StrafeCamera( Pose, View, -0.005f);}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUniform1f( glGetUniformLocation( GLSL_Prog[0], "timer"), timer);
		glUniform1f( glGetUniformLocation( GLSL_Prog[0], "frustum_cube"), 0.10f);

		glUseProgram( GLSL_Prog[0]);
		// for(int x = 0; x < 10; x++){
		// 	for(int y = 0; y < 10; y++){
		// 		for(int z = 0; z < 10; z++){
		// 			gMatrixTranslation( GLSL_Prog[0], BOXX[x], BOXX[y], BOXX[z]);
		// 			gMatrixRotation( GLSL_Prog[0], rot, 0.0f, 0.0f, 1.0f);
		// 			gMatrixRotation( GLSL_Prog[0], rot, 0.0f, 1.0f, 0.0f);
		// 			gMatrixRotation( GLSL_Prog[0], rot, 1.0f, 0.0f, 0.0f);

		// 			if( CubeinFrustum( 1.0f) >= 40){
		// 			// if( result > 40){						// 40, we are not talkng about intercepting 
		// 				glActiveTexture(GL_TEXTURE0);		
		// 				glBindTexture(GL_TEXTURE_2D, m_texture);

		// 				Draw_Object(VBO[0], 36);
		// 			// }
		// 			}
		// 			gPopMatrix( GLSL_Prog[0], "modelMatrix");
		// 		}
		// 	}
		// }
		gMatrixTranslation( GLSL_Prog[0], 0.0f, 0.0f, 10.0f);
		gMatrixRotation( GLSL_Prog[0], rot, 0.0f, 0.0f, 1.0f);
		gMatrixRotation( GLSL_Prog[0], rot, 0.0f, 1.0f, 0.0f);
		gMatrixRotation( GLSL_Prog[0], rot, 1.0f, 0.0f, 0.0f);

		if( CubeinFrustum( 1.0f) >= 40){
		// if( result > 40){						// 40, we are not talkng about intercepting 
   			glActiveTexture(GL_TEXTURE0);		
			glBindTexture(GL_TEXTURE_2D, m_texture);

			Draw_Object(VBO[0], 36);
		// }
		}
		gPopMatrix( GLSL_Prog[0], "modelMatrix");

		// gMatrixTranslation( GLSL_Prog[0], 2.0f, 0.0f, 10.0f);
		// gMatrixRotation( GLSL_Prog[0], rot, 0.0f, 0.0f, 1.0f);
		// gMatrixRotation( GLSL_Prog[0], rot, 0.0f, 1.0f, 0.0f);
		// gMatrixRotation( GLSL_Prog[0], rot, 1.0f, 0.0f, 0.0f);

		// if( CubeinFrustum( 1.0f) >= 40){
		// // if( result > 40){						// 40, we are not talkng about intercepting 
   		// 	glActiveTexture(GL_TEXTURE0);		
		// 	glBindTexture(GL_TEXTURE_2D, m_texture);

		// 	Draw_Object(VBO[0], 36);
		// // }
		// }
		// gPopMatrix( GLSL_Prog[0], "modelMatrix");




		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			fprintf(stderr, "OpenGL error in mainloop: %d\n", error);
			Shut_Down(1);
		}

		glfwSwapBuffers(wnd);
		glfwPollEvents();
	}

	glDeleteTextures(1, &m_texture);
}


//shut down!!
void Shut_Down(int return_code){

	glDeleteBuffers(1, &VAO[2]);
	glDeleteBuffers(1, &VAO[1]);
	glDeleteVertexArrays(1, &VAO[0]);

	glDeleteBuffers(1, &VBO[2]);
	glDeleteBuffers(1, &VBO[1]);
	glDeleteVertexArrays(1, &VBO[0]);

	if( GLSL_Prog[0]){
		glDeleteProgram( GLSL_Prog[0]);
		glDeleteShader( GLSL_Prog[1]);
		glDeleteShader( GLSL_Prog[2]);		
	}	

	glfwTerminate();
	exit(return_code);
}





