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
	
	// render the object
	void RenderObj::render() {

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glDrawArrays(GL_TRIANGLES, 0, 3);

	}

	void RenderObj::initBuffers() {

		// generates buffer 
		glGenBuffers(1, &vertexBuffer);

	}

	// getters
	
	// setters
	void RenderObj::putVert(float i) {

		verts[vertCount];
		vertCount++;

	}
	
	// Place data into the buffer
	void RenderObj::updateVertBuffer() {

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	}

	
	// Constructor
	RenderObj::RenderObj() {

		vertCount = 0;

	}

	// Destructor
	RenderObj::~RenderObj() {

		glDeleteBuffers(1, &vertexBuffer);

	}


}// Namespace PiratesLife
