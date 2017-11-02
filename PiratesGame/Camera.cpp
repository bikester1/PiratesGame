#include "Camera.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/trigonometric.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <math.h>
#include <iostream>

namespace PiratesLife {
	// getters
	glm::mat4x4 Camera::getPerspectiveMat() {
		if (cameraUpdated)
			updateMats();

		return perspectiveMat;
	}

	glm::mat4x4 Camera::getViewMat() {
		if (cameraUpdated)
			updateMats();

		return viewMat;
	}

	glm::vec3 Camera::getPos() {
		return pos;
	}

	glm::vec3 Camera::getRot() {
		return rot;
	}

	float Camera::getFOV() {
		return fov;
	}

	float Camera::getNearCP() {
		return nearCP;
	}

	float Camera::getFarCP() {
		return farCP;
	}

	float Camera::getAspect() {
		return aspect;
	}

	bool Camera::isUpdated() {
		return cameraUpdated;
	}

	glm::vec3 Camera::getLookAt() {
		lookAt = glm::rotateX(glm::vec3(0.0f, 0.0f, -1.0f), glm::radians(rot.x));
		lookAt = glm::rotateY(lookAt, glm::radians(rot.y));

		return lookAt;
	}

	bool Camera::getForward() {
		return forward;
	}

	bool Camera::getBack() {
		return back;
	}

	bool Camera::getLeft() {
		return left;
	}

	bool Camera::getRight() {
		return right;
	}

	float Camera::getSpeed() {
		return speed;
	}


	//setters
	void Camera::setPos(glm::vec3 pos) {
		cameraUpdated = true;
		Camera::pos = pos;
	}

	void Camera::setRot(glm::vec3 rot) {
		cameraUpdated = true;
		Camera::rot = rot;

		if (Camera::rot.x > 360.0f)
			Camera::rot.x -= 360.0f;

		if (Camera::rot.y > 360.0f)
			Camera::rot.y -= 360.0f;

		if (Camera::rot.z > 360.0f)
			Camera::rot.z -= 360.0f;


		if (Camera::rot.x < 0.0f)
			Camera::rot.x += 360.0f;

		if (Camera::rot.y < 0.0f)
			Camera::rot.y += 360.0f;

		if (Camera::rot.z < 0.0f)
			Camera::rot.z += 360.0f;
	}

	void Camera::setFOV(float fov) {
		cameraUpdated = true;
		Camera::fov = fov;
	}

	void Camera::setNearCP(float nearCP) {
		cameraUpdated = true;
		Camera::nearCP = nearCP;
	}

	void Camera::setFarCP(float farCP) {
		cameraUpdated = true;
		Camera::farCP = farCP;
	}

	void Camera::setAspect(float aspect) {
		cameraUpdated = true;
		Camera::aspect = aspect;
	}

	void Camera::setForward(bool forward) {
		Camera::forward = forward;
	}

	void Camera::setBack(bool back) {
		Camera::back = back;
	}

	void Camera::setLeft(bool left) {
		Camera::left = left;
	}

	void Camera::setRight(bool right) {
		Camera::right = right;
	}

	void Camera::setSpeed(float speed) {
		Camera::speed = speed;
	}

	void Camera::updateMats() {
		perspectiveMat = glm::perspective(glm::radians(fov), aspect, nearCP, farCP);
		viewMat = glm::rotate(glm::mat4x4(1.0f), glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
		viewMat = glm::rotate(viewMat, glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
		viewMat = glm::rotate(viewMat, glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
		viewMat = glm::translate(viewMat, glm::vec3(-pos.x, -pos.y, -pos.z));

		cameraUpdated = false;
	}

	void Camera::updatePos() {

		cameraUpdated = true;
		glm::vec3 vec = glm::vec3(0.0f, 0.0f, 0.0f);

		if (forward)
			vec.z -= 1.0f;

		if (back)
			vec.z += 1.0f;

		if (left)
			vec.x -= 1.0f;

		if (right)
			vec.x += 1.0f;


		moveTowards(vec);
	}

	void Camera::moveTowards(glm::vec3 vec) {
		if (vec.x == 0.0f && vec.y == 0.0f && vec.z == 0.0f)
			return;

		vec = glm::normalize(vec);
		vec = glm::rotate(vec, glm::radians(-rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
		vec = glm::rotate(vec, glm::radians(-rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
		vec = glm::rotate(vec, glm::radians(-rot.z), glm::vec3(0.0f, 0.0f, 1.0f));

		vec = vec * speed;
		std::cout << pos.x << " " << pos.y << " " << pos.z << " " << std::endl;
		pos += vec;
	}

	Camera::Camera(float fov, float aspect, float nearCP, float farCP)
	{
		Camera::fov = fov;
		Camera::aspect = aspect;
		Camera::nearCP = nearCP;
		Camera::farCP = farCP;
		rot = glm::vec3(0.0f, 0.0f, 0.0f);
		pos = glm::vec3(0.0f, 0.0f, 10.0f);
		forward = false;
		back = false;
		left = false;
		right = false;
		speed = 0.1f;
	}


	Camera::~Camera()
	{
	}

}