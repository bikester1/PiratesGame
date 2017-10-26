/*
* RenderObj.cpp
*
*  Created on: Oct 26, 2017
*      Author: Brenden Cohen
*/

#include "RenderObj.h"

#include <GL/glew.h>
#include <Vector>

namespace PiratesLife {

	void RenderObj::render() {

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glDrawArrays(GL_TRIANGLES, 0, 3);

	}

	// getters
	std::vector <int> RenderObj::getVec() {

		return vec;

	}

	void RenderObj::putVec(int i) {

		RenderObj::vec.push_back(i);

	}

	// Place data into the buffer
	void RenderObj::updateVertBuffer() {

		glBindBuffer(GL_ARRAY_BUFFER, RenderObj::vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(RenderObj::vec), RenderObj::vec, GL_STATIC_DRAW);

	}


	// Constructor
	RenderObj::RenderObj() {

		// generate buffer
		glGenBuffers(1, &vertexBuffer);

	}

	// Destructor
	RenderObj::~RenderObj() {

		glDeleteBuffers(1, &vertexBuffer);

	}


}// Namespace PiratesLife
