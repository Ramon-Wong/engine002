#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
const  int WIDTH = 800;
const  int HEIGHT = 600;

GLuint vertexbuffer;

void Initialization()
{
	glfwInit(); //first initialize GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//core-profile means we'll get access to a smaller subset of OpenGL
	//features (without backwards-compatible features we no longer need)
}



void gladloader()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;

	}

	/*

	We pass GLAD the function to load the adress of the OpenGL function pointers which is OS-specific.
	GLFW gives us glfwGetProcAddress that defines
	the correct function based on which OS we're compiling for.


	*/
}

void processInput(GLFWwindow *window)
{/*
 We also want to have some form of input control in GLFW and we can achieve
 this with several of GLFW's input functions. We'll be using GLFW's glfwGetKey function
 that takes the window as input together with a key. The function returns whether
 this key is currently being pressed.
 We're creating a processInput function to keep all input code organized:
 */
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Rendering()
{
	glViewport(0, 0, 800, 600);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

float Triangle_vertices[] = {
	 0.0f,  0.5f,  0.0f,
   0.5f, -0.5f,  0.0f,
  -0.5f, -0.5f,  0.0f
};

int main()
{
	Initialization();
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Triangle", NULL, NULL);
	/*he glfwCreateWindow function requires the window width and height as its first two arguments respectively.
	The third argument allows us to create a name for the window
	*/

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	/* The function returns a GLFWwindow object that we'll later need for other GLFW operations.
	After that we tell GLFW to make the
	context of our window the main context on the current thread.
	*/

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	gladloader();

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle_vertices), Triangle_vertices, GL_STATIC_DRAW);

	while (!glfwWindowShouldClose(window))
	{
		//keeps on running until we tell GLFW to stop
		processInput(window);
		Rendering();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}