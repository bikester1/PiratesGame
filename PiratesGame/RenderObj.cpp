/*
* RenderObj.cpp
*
*  Created on: Oct 26, 2017
*      Author: Brenden Cohen
*/

#include "RenderObj.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/gtx/transform.hpp>



namespace PiratesLife {
	
	// render the object
	void RenderObj::render() {

		if (vertexBuffer == 0)
			initBuffers();

		if (myVertices.size() == 0)
			return;
		
		getMVP();


		// enable vertex attribute
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, stride, vertexAttribOffset);
		glEnableVertexAttribArray(0);

		// enable normal attribute if enabled
		if (hasNormals == true) {
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, stride, normalAttribOffset);
			glEnableVertexAttribArray(1);
		}

		// enable texture attribute if enabled
		if (hasTexture == true) {
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, stride, textureAttribOffset);
			glEnableVertexAttribArray(2);
		}

		// draw the buffer
		glDrawArrays(GL_TRIANGLES, 0, numOfVertices);


		// disable Vertex Attribs to be used in another draw call
		glDisableVertexAttribArray(0);

		if(hasNormals == true)
			glDisableVertexAttribArray(1);

		if(hasTexture == true)
			glDisableVertexAttribArray(2);
	}

	void RenderObj::importOBJ(std::string filePath) {
		// our fileStream to the obj file
		std::ifstream fileStream(filePath.c_str(), std::ios::in);
		std::string line;
		std::vector<glm::vec3> tempVertArr;
		std::vector<glm::vec3> tempNormArr;
		std::vector<glm::vec3> tempTexArr;
		std::vector<glm::vec3> *faceArr = new std::vector<glm::vec3>();
		std::string::size_type index;
		int i, vertIndex[3], normIndex[3], texIndex[3];

		glm::vec3 tempVec;

		// clear our previously hedl vertices
		myVertices.clear();

		if (fileStream.is_open()) {
			while (getline(fileStream, line)) {
				index = 0;

				// skip comments
				if (line[0] == '#')
					continue;
				// check if vertex
				else if (line[0] == 'v' && line[1] == ' ') {

					sscanf_s(line.c_str(), "%*s %f %f %f", &tempVec.x, &tempVec.y, &tempVec.z);
					tempVertArr.push_back(tempVec);

				}
				else if (line[0] == 'v' && line[1] == 'n') {

					sscanf_s(line.c_str(), "%*s %f %f %f", &tempVec.x, &tempVec.y, &tempVec.z);
					tempNormArr.push_back(tempVec);

				}
				else if (line[0] == 'v' && line[1] == 't') {

					sscanf_s(line.c_str(), "%*s %f %f %f", &tempVec.x, &tempVec.y, &tempVec.z);
					tempTexArr.push_back(tempVec);

				}
				// cehck if face
				else if (line[0] == 'f' && line[1] == ' ') {
					// if we only have vertices parse out faces with only vertices
					if (tempVertArr.size() > 0 && tempNormArr.size() == 0 && tempTexArr.size() == 0) {

						sscanf_s(line.c_str(), "%*s %d %d %d", &vertIndex[0], &vertIndex[1], &vertIndex[2]);
						myVertices.push_back(tempVertArr[vertIndex[0] - 1]);
						myVertices.push_back(tempVertArr[vertIndex[1] - 1]);
						myVertices.push_back(tempVertArr[vertIndex[2] - 1]);

					}
					// if we have vertices and normals
					else if (tempVertArr.size() > 0 && tempNormArr.size() > 0 && tempTexArr.size() == 0) {

						sscanf_s(line.c_str(), "%*s %d//%d %d//%d %d//%d", &vertIndex[0], &normIndex[0], &vertIndex[1], &normIndex[1], &vertIndex[2], &normIndex[2]);
						myVertices.push_back(tempVertArr[vertIndex[0] - 1]);
						myVertices.push_back(tempNormArr[normIndex[0] - 1]);
						myVertices.push_back(tempVertArr[vertIndex[1] - 1]);
						myVertices.push_back(tempNormArr[normIndex[1] - 1]);
						myVertices.push_back(tempVertArr[vertIndex[2] - 1]);
						myVertices.push_back(tempNormArr[normIndex[2] - 1]);

					}
				}
			}
		}

		if (tempVertArr.size() > 0 && tempNormArr.size() == 0 && tempTexArr.size() == 0) {
			stride = sizeof(glm::vec3);
			vertexAttribOffset = (GLvoid**)0;
			normalAttribOffset = (GLvoid**)0;
			textureAttribOffset = (GLvoid**)0;
			hasNormals = false;
			hasTexture = false;
			numOfVertices = myVertices.size();
		}
		
		else if (tempVertArr.size() > 0 && tempNormArr.size() > 0 && tempTexArr.size() == 0) {
			stride = sizeof(glm::vec3) * 2;
			vertexAttribOffset = (GLvoid**)0;
			normalAttribOffset = (GLvoid**)sizeof(glm::vec3);
			textureAttribOffset = (GLvoid**)0;
			hasNormals = true;
			hasTexture = false;
			numOfVertices = myVertices.size()/2;
		}

		else if (tempVertArr.size() > 0 && tempNormArr.size() > 0 && tempTexArr.size() > 0) {
			stride = sizeof(glm::vec3) * 3;
			vertexAttribOffset = (GLvoid**)0;
			normalAttribOffset = (GLvoid**)sizeof(glm::vec3);
			textureAttribOffset = (GLvoid**)(sizeof(glm::vec3) * 2);
			hasNormals = true;
			hasTexture = true;
			numOfVertices = myVertices.size()/3;
		}

	}

	// initialize buffers
	void RenderObj::initBuffers() {

		// generates buffer 
		if (vertexBuffer == 0) {
			glGenBuffers(1, &vertexBuffer);
			MVPMatrix = glGetUniformLocation(program, "MVP");
			modelMatrix = glGetUniformLocation(program, "M");
			viewMatrix = glGetUniformLocation(program, "V");
		}

	}
	
	// Place data into the buffer
	void RenderObj::updateVertBuffer() {
		// init vbo if it hasnt already been
		if (vertexBuffer == 0)
			initBuffers();

		// if we have no data there is nothing to draw
		if (myVertices.size() == 0)
			return;

		// bind buffers and add data
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * myVertices.size(), &myVertices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, stride, vertexAttribOffset);
		glEnableVertexAttribArray(0);
		//glGetBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * vertCount, temp);

	}

	float RenderObj::getPosX() {
		return pos.x;
	}

	float RenderObj::getPosY() {
		return pos.y;
	}

	float RenderObj::getPosZ() {
		return pos.z;
	}

	glm::vec3 RenderObj::getPos(float x, float y, float z) {
		return pos;
	}

	void RenderObj::loadTexture(std::string str) {

		

	}

	glm::mat4x4 RenderObj::getMVP() {
		glm::mat4x4 perspectiveMat = cam->getPerspectiveMat();
		glm::mat4x4 viewMat = cam->getViewMat();
		glm::mat4x4 rotateMat = glm::rotate(glm::mat4x4(1.0f), rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
		rotateMat = glm::rotate(rotateMat, rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
		rotateMat = glm::rotate(rotateMat, rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4x4 modelMat = glm::translate(glm::mat4x4(1.0f), pos) * rotateMat * glm::scale(glm::mat4x4(1.0f),scale);
		glm::mat4x4 MVPMat = (perspectiveMat * viewMat * modelMat);


		glUniformMatrix4fv(MVPMatrix, 1, GL_FALSE, &(MVPMat[0][0]));
		glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, &(viewMat[0][0]));
		glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, &(modelMat[0][0]));

		return MVPMat;
	}

	int RenderObj::putVert(float x, float y, float z) {

		myVertices.push_back(glm::vec3(x, y, z));
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

	void RenderObj::setScale(glm::vec3 scale) {
		RenderObj::scale = scale;
	}

	void RenderObj::setPos(float x, float y, float z) {
		pos = glm::vec3(x, y, z);
	}

	void RenderObj::setProgram(unsigned int program) {
		RenderObj::program = program;
	}

	
	// Constructor
	RenderObj::RenderObj() {

		vertexBuffer = 0;
		vertSize = 3;
		stride = sizeof(float) * vertSize;
		scale = glm::vec3(1.0f, 1.0f, 1.0f);
		rot = glm::vec3(0.0f, 0.0f, 0.0f);
		pos = glm::vec3(0.0f, 0.0f, 0.0f);
		cam = NULL;

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
