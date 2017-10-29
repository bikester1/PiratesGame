#pragma once

#include "Camera.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace PiratesLife{

	class InputHandler
	{
	public:

		static Camera *activeCam;
		static double prevX;
		static double prevY;

		static void procInput(GLFWwindow *window, int key, int scancode, int action, int mods);

		static void procCursor(GLFWwindow *window, double x, double y);

		static void setCam(Camera *cam);

		InputHandler();
		~InputHandler();
	};

}

