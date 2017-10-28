/*
* RenderObj.cpp
*
*  Created on: Oct 26, 2017
*      Author: Brenden Cohen
*/

#include "RenderObj.h"

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/gtx/transform.hpp>

#include "managedArray.cpp"

namespace PiratesLife {
	
	// render the object
	void RenderObj::render() {

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, vertSize, GL_FLOAT, GL_TRUE, stride, 0);
		glDrawArrays(GL_TRIANGLES, 0, myVertices.getSize());

		glDisableVertexAttribArray(0);
	}

	void RenderObj::initBuffers() {

		// generates buffer 
		glGenBuffers(1, &vertexBuffer);

	}
	
	// Place data into the buffer
	void RenderObj::updateVertBuffer() {

		float *vertices = new float[(myVertices.getSize() * 3)];
		glm::vec3 tempVec3;
		int i;

		for (i = 0; i < myVertices.getSize(); i++) {
			tempVec3 = myVertices.getVec(i);
			vertices[(i * 3) + 0] = tempVec3.x;
			vertices[(i * 3) + 1] = tempVec3.y;
			vertices[(i * 3) + 2] = tempVec3.z;
		}

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * myVertices.getSize() * vertSize, vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, vertSize, GL_FLOAT, GL_TRUE, stride, 0);
		glEnableVertexAttribArray(0);
		//glGetBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * vertCount, temp);

		delete vertices;

	}

	float RenderObj::getPosX(float x) {
		return pos.x;
	}

	float RenderObj::getPosY(float y) {
		return pos.y;
	}

	float RenderObj::getPosZ(float z) {
		return pos.z;
	}

	glm::vec3 RenderObj::getPos(float x, float y, float z) {
		return pos;
	}

	glm::mat4x4 RenderObj::getMVP() {
		glm::mat4x4 perspectiveMat = cam->getPerspectiveMat();
		glm::mat4x4 viewMat = cam->getViewMat();
		glm::mat4x4 rotateMat = glm::rotate(glm::mat4x4(1.0f), rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
		rotateMat = glm::rotate(rotateMat, 20.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		rotateMat = glm::rotate(rotateMat, rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4x4 modelMat = glm::translate(glm::mat4x4(1.0f), pos) * rotateMat * glm::scale(glm::mat4x4(0.1f),scale);

		return perspectiveMat * viewMat * modelMat;
	}

	int RenderObj::putVert(float x, float y, float z) {

		myVertices.putVec(glm::vec3(x, y, z));
		return 1;

	}

	void RenderObj::setPosX(float x) {
		pos.x = x;
	}

	void RenderObj::setPosY(float y) {
		pos.y = y;
	}

	void RenderObj::setPosZ(float z) {
		pos.z = z;
	}

	void RenderObj::setPos(float x, float y, float z) {
		pos = glm::vec3(x, y, z);
	}

	
	// Constructor
	RenderObj::RenderObj() {

		vertexBuffer = 0;
		vertSize = 3;
		stride = sizeof(float) * vertSize;
		scale = glm::vec3(1.0f, 1.0f, 1.0f);
		rot = glm::vec3(0.0f, 0.0f, 0.0f);

	}

	// destructor
	RenderObj::RenderObj(int vertSize) : RenderObj() {

		RenderObj::vertSize = vertSize;
		stride = sizeof(float) * vertSize;

	}

	RenderObj::RenderObj(PiratesLife::Camera *cam) : RenderObj() {
		RenderObj::cam = cam;
	}

	// Destructor
	RenderObj::~RenderObj() {
		if (vertexBuffer != 0)
			glDeleteBuffers(1, &vertexBuffer);
	}


}// Namespace PiratesLife
