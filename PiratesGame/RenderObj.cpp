/*
* RenderObj.cpp
*
*  Created on: Oct 26, 2017
*      Author: Brenden Cohen
*/

#include "RenderObj.h"

#include <GL/glew.h>
#include <glm/vec3.hpp>

#include "managedArray.cpp"

namespace PiratesLife {
	
	// render the object
	void RenderObj::render() {

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, vertSize, GL_FLOAT, GL_TRUE, stride, 0);
		glDrawArrays(GL_LINE_LOOP, 0, myVertices.getSize());

		glDisableVertexAttribArray(0);
	}

	void RenderObj::initBuffers() {

		// generates buffer 
		glGenBuffers(1, &vertexBuffer);

	}

	// Attempts to add to the verts array
	// Returns 1 on success
	// returns 0 on failure
	int RenderObj::putVert(float x, float y, float z) {

		myVertices.putVec(glm::vec3(x, y, z));
		return 1;

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

	
	// Constructor
	RenderObj::RenderObj() {

		vertSize = 3;
		stride = sizeof(float) * vertSize;

	}

	// destructor
	RenderObj::RenderObj(int vertSize) {

		RenderObj::vertSize = vertSize;
		stride = sizeof(float) * vertSize;

	}

	// Destructor
	RenderObj::~RenderObj() {

		glDeleteBuffers(1, &vertexBuffer);

	}


}// Namespace PiratesLife
