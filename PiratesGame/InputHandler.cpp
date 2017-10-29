#include "InputHandler.h"


namespace PiratesLife{

	Camera *InputHandler::activeCam = NULL;
	double InputHandler::prevX = 0;
	double InputHandler::prevY = 0;

	void InputHandler::procInput(GLFWwindow *window, int key, int scancode, int action, int mods) {

		if (activeCam == NULL)
			return;
		// key presses
		if (key == GLFW_KEY_W && action == GLFW_PRESS)
			activeCam->setForward(true);

		if (key == GLFW_KEY_S && action == GLFW_PRESS)
			activeCam->setBack(true);

		if (key == GLFW_KEY_A && action == GLFW_PRESS)
			activeCam->setLeft(true);

		if (key == GLFW_KEY_D && action == GLFW_PRESS)
			activeCam->setRight(true);


		// key releases
		if (key == GLFW_KEY_W && action == GLFW_RELEASE)
			activeCam->setForward(false);

		if (key == GLFW_KEY_S && action == GLFW_RELEASE)
			activeCam->setBack(false);

		if (key == GLFW_KEY_A && action == GLFW_RELEASE)
			activeCam->setLeft(false);

		if (key == GLFW_KEY_D && action == GLFW_RELEASE)
			activeCam->setRight(false);

		if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
			glfwDestroyWindow(window);
	}

	void InputHandler::procCursor(GLFWwindow *window, double x, double y) {
		if (x - prevX != 0 || y - prevY != 0) {
			glm::vec3  tempRot = activeCam->getRot();
			activeCam->setRot(glm::vec3(tempRot.x + y - prevY, tempRot.y + x - prevX, 0.0f));
			prevY = y;
			prevX = x;
		}
		
	}

	void InputHandler::setCam(PiratesLife::Camera *cam) {
		activeCam = cam;
	}

	InputHandler::InputHandler()
	{
	}


	InputHandler::~InputHandler()
	{
	}

}