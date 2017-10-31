/*
* Main.cpp
*
*  Created on: Oct 25, 2017
*      Author: Brenden Cohen
*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <String>
#include "RenderObj.h"
#include "PiratesLife.h"
#include "InputHandler.h"


int main(void)
{
	GLFWwindow *window = NULL;
	int width = 1920;
	int height = 1000;
	PiratesLife::Camera cam(70.0f, (float)width / (float)height, 0.1f, 1000.0f);
	cam.setPos(glm::vec3(0.0f, 0.0f, 0.0f));
	PiratesLife::RenderObj obj = PiratesLife::RenderObj(&cam);
	PiratesLife::InputHandler::setCam(&cam);
	cam.setSpeed(0.1f);
	unsigned int program;
	int i = 0;

	/*
	// define some verticies to draw 
	float verts[24] = {
		1.072369f, -0.950795f, -1.224498f,
		1.072369f, -0.950795f, 0.775502f,
		-0.927631f, -0.950795f, 0.775502f,
		-0.927631f, -0.950795f, -1.224499f,
		1.072370f, 1.049205f, -1.224498f,
		1.072368f, 1.049205f, 0.775502f,
		-0.927631f, 1.049205f, 0.775501f,
		-0.927631f, 1.049205f, -1.224498f
		//0.0f, 0.0f, 2.0f,
		//1.0f, 0.0f, -1.0f,
		//1.0f, 1.0f, -1.0f
	};

	// give our obj the vertices
	for (i = 0; i + 2 < sizeof(verts) / sizeof(float); i += 3) {
		obj.putVert(verts[i], verts[i + 1], verts[i + 2]);
	}
	*/

	// init graphics libraries
	if (!initGL(&window, width, height, "Pirates Life For Me!!")) {
		printf("Exiting Program: initGL error\n");
		return -1;
	}

	if (!(program = loadShaders("Shaders\\VertexShader.txt", "Shaders\\FragmentShader.txt"))) {
		printf("Exiting Program: shader error\n");
		return -1;
	}

	//obj.setVertArray(importer.ImportVerticesFromOBJ("Models\\untitled.obj"));

	// init and update buffers
	obj.importOBJ("Models\\test3.obj");
	obj.setProgram(program);
	obj.initBuffers();
	obj.updateVertBuffer();

	int j;

	glm::vec3 rot;

	glfwSetKeyCallback(window, PiratesLife::InputHandler::procInput);
	glfwSetCursorPosCallback(window, PiratesLife::InputHandler::procCursor);
	// Loop until the user closes the window

	//glCullFace(GL_BACK);

	while (!glfwWindowShouldClose(window))
	{
		// Render here
		cam.updatePos();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(program);

		//obj.render();

		for (i = 0; i < 20; i++) {
			for (j = 0; j < 20; j++) {
				obj.setPosX(3.0f * j);
				obj.setPosZ(5.0f * i);
				obj.render();
			}
		}
		obj.setPosX(0.0f);

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

// init the graphics library
// return 1 on success
// return -1 on failure 
int initGL(GLFWwindow **window, int width, int height, char *str) {
	// Initialize glfw
	if (!glfwInit()) {
		printf("Error: glfw failed to initialize.\n");
		return -1;
	}


	// Create a windowed mode window and its OpenGL context
	*window = glfwCreateWindow(width, height, str, NULL, NULL);
	if (!*window)
	{
		printf("Error: glfw failed to create window properly.\n");
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(*window);

	// Finally init GLEW 
	if (glewInit() != GLEW_OK) {
		printf("Error: GLEW failed to initialize properly.\n");
		return -1;
	}

	// configure cursor
	glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);

	return 1;
}

int loadShaders(char *vertexShaderPath, char *fragmentShaderPath) {
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// init stream and string
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexShaderPath, std::ios::in);

	// open vertexShaderCode
	if (vertexShaderStream.is_open()) {
		std::string line = "";
		while (getline(vertexShaderStream, line))
			vertexShaderCode += line + "\n";
		vertexShaderStream.close();
	}
	else {
		return -1;
	}

	// init stream and string
	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragmentShaderPath, std::ios::in);

	// open fragmentShaderCode
	if (fragmentShaderStream.is_open()) {
		std::string line = "";
		while (getline(fragmentShaderStream, line))
			fragmentShaderCode += line + "\n";
		fragmentShaderStream.close();
	}
	else {
		return -1;
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// compile shaders
	char const *vertexSourcePtr = vertexShaderCode.c_str();
	glShaderSource(vertexShader, 1, &vertexSourcePtr, NULL);
	glCompileShader(vertexShader);
	char const *fragmentSourcePtr = fragmentShaderCode.c_str();
	glShaderSource(fragmentShader, 1, &fragmentSourcePtr, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(fragmentShader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// attatch and link shaders
	int program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	// clean up clean up everybody do your share
	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}


