#include "functions.h"






void Main_Loop(){
    int i = 0;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0); // Adjust parameters as needed

    // Set up the modelview matrix (camera position and orientation)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (!glfwWindowShouldClose(window)) {
        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        // Set up the viewport
        gluLookAt(0.0, 0.0, 5.0, // Eye position
                  0.0, 0.0, 0.0, // Look at position (center)
                  0.0, 1.0, 0.0); // Up direction
        // Implement your rendering code here, including any objects or transformations

        if( i == 0){
	        float   proj[16];								// This will hold our projection matrix
	        float   modl[16];								// This will hold our modelview matrix
	        float   clip[16];		            

	        glGetFloatv( GL_PROJECTION_MATRIX, proj );
	        glGetFloatv( GL_MODELVIEW_MATRIX, modl );

	        clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
	        clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
	        clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
	        clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

	        clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
	        clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
	        clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
	        clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

	        clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
	        clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
	        clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
	        clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

	        clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
	        clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
	        clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
	        clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];


            for(int n = 0; n < 4; n++){
                printf("\n clip: %f//%f//%f//%f", clip[0+n], clip[1+n], clip[2+n], clip[3+n]);
            }    

	        float   projmatrix[16];
	        float   modelview[16];
	        float   ProjModel[16];	

            MLoadIdentity(projmatrix);
            MLoadIdentity(modelview);

            float Pose[] = { 0.0, 0.0, 5.0};    // Eye position
            float View[] = { 0.0, 0.0, 0.0};    // Look at position (center)
            float UpVx[] = { 0.0, 1.0, 0.0};    // Up direction
            float aspect_ratio = 800 / 600;

            // gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0); // Adjust parameters as needed
            MFrustum( (float*)projmatrix, 0.5f, -0.5f, -0.5f * aspect_ratio, 0.5f * aspect_ratio, 0.1f, 100.0f);	
            LookAtM(modelview, Pose, View, UpVx);
            MMultiply( ProjModel, projmatrix, modelview);

            printf("\n");
            for(int n = 0; n < 4; n++){
                printf("\n ProjModel: %f//%f//%f//%f", ProjModel[0+n], ProjModel[1+n], ProjModel[2+n], ProjModel[3+n]);
            }    
            printf("\n end");

            i = 1;
        }

        glBegin(GL_QUADS);
        glVertex3f(-0.5f,-0.5f, 0.0f);
        glVertex3f( 0.5f,-0.5f, 0.0f);
        glVertex3f( 0.5f, 0.5f, 0.0f);
        glVertex3f(-0.5f, 0.5f, 0.0f);
        glEnd();

        // Swap the front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }    
}