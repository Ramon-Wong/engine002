#include "functions.h"





void Main_Loop(){


    // Implement your frustum culling logic here to decide if the square is visible

	while(!glfwWindowShouldClose(window)){
    //     glClear(GL_COLOR_BUFFER_BIT);

    //     glBegin(GL_QUADS);
    //     glVertex2f(-0.5f, -0.5f);  // Bottom-left corner
    //     glVertex2f(0.5f, -0.5f);   // Bottom-right corner
    //     glVertex2f(0.5f, 0.5f);    // Top-right corner
    //     glVertex2f(-0.5f, 0.5f);   // Top-left corner
    //     glEnd();
    }
    
    glfwSwapBuffers(window);
    glfwPollEvents();
}


