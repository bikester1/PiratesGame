/*
* Main.cpp
*
*  Created on: Oct 25, 2017
*      Author: Brenden Cohen
*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "RenderObj.h"

int main(void)
{
	GLFWwindow* window;
	//PiratesLife::RenderObj obj = new PiratesLife::RenderObj();
	int i = 0;

	float verts[6] = {
		-0.5f, -0.5f,
		0.0f, 0.5f,
		0.5f, -0.5f,
	};

	// give our obj the vertices
	//for (i = 0; i < sizeof(verts) / sizeof(float); i++)
	//	obj.putVec(verts[i]);



	// Initialize the library
	if (!glfwInit())
		return -1;

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "Test?" << std::endl;
	}

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// Render here
		glClear(GL_COLOR_BUFFER_BIT);

		//obj.render();

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

