#pragma once

#include <glm\vec3.hpp>
#include <glm/mat4x4.hpp>

namespace PiratesLife {

	class Camera
	{
	public:

		glm::mat4x4 getPerspectiveMat();

		glm::mat4x4 getViewMat();


		// getters
		glm::vec3 getPos();

		glm::vec3 getRot();

		float getFOV();

		float getNearCP();

		float getFarCP();

		float getAspect();

		bool Camera::isUpdated();

		glm::vec3 Camera::getLookAt();


		//setters
		void setPos(glm::vec3 pos);

		void setRot(glm::vec3 rot);

		void setFOV(float fov);

		void setNearCP(float nearCP);

		void setFarCP(float farCP);

		void setAspect(float aspect);

		void updateMats();

		Camera(float fov, float aspect, float nearCP, float farCP);
		~Camera();

	private:
		glm::vec3 pos;
		glm::vec3 rot;
		glm::mat4x4 perspectiveMat;
		glm::mat4x4 viewMat;
		glm::vec3 lookAt;

		float fov;
		float nearCP;
		float farCP;
		float aspect;
		bool cameraUpdated;

	};

}
