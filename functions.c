#include "functions.h"






void Shutdown(void){
    glfwTerminate();
}


void Mainloop(void){

	  glEnable(GL_DEPTH_TEST);                              // enable depth-testing
	  glDepthFunc(GL_LESS);                                 // depth-testing interprets a smaller value as "closer"
	  glViewport( 0, 0, 800, 600);

    GLFWwindow * wnd = glfwGetCurrentContext();

	  while(!glfwWindowShouldClose(wnd)) {                  // Render the game until the user closes the window.
		  // wipe the drawing surface clear
		  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      // Break the while loop when the user presses the Escape key.
		  if (glfwGetKey(wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS) { break;}


      

		  glfwPollEvents();                                   // Poll events to check for user input.
		  glfwSwapBuffers(wnd);                               // Swap buffers to display the rendered image.
	  }	

    Shutdown();
}
