#include "Camera.h"
#include <math.h>
#include <glm/trigonometric.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace PiratesLife {

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


	// getters
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

	void Camera::updateMats() {
		perspectiveMat = glm::perspective(glm::radians(fov), aspect, nearCP, farCP);
		viewMat = glm::lookAt(pos, getLookAt(), glm::vec3(0, 1, 0));

		cameraUpdated = false;
	}


	Camera::Camera(float fov, float aspect, float nearCP, float farCP)
	{
		Camera::fov = fov;
		Camera::aspect = aspect;
		Camera::nearCP = nearCP;
		Camera::farCP = farCP;
		rot = glm::vec3(0.0f, 0.0f, 0.0f);
		pos = glm::vec3(0.0f, 0.0f, 10.0f);
	}


	Camera::~Camera()
	{
	}

}