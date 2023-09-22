#include "functions.h"






void Main_Loop(){

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