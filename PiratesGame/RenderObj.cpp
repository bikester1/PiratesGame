/*
* RenderObj.cpp
*
*  Created on: Oct 26, 2017
*      Author: Brenden Cohen
*/

#include "RenderObj.h"

#include <GL/glew.h>
#include <Vector>
#include "vec3Array.h"

namespace PiratesLife {
	
	// render the object
	void RenderObj::render() {

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, vertSize, GL_FLOAT, GL_TRUE, stride, 0);
		glDrawArrays(GL_LINE_LOOP, 0, vertices.getSize() / vertSize);

		glDisableVertexAttribArray(0);
	}

	void RenderObj::initBuffers() {

		// generates buffer 
		glGenBuffers(1, &vertexBuffer);

	}

	// getters
	
	//---------//
	// setters //
	//---------//

	// Attempts to add to the verts array
	// Returns 0 on success
	// returns -1 on failure
	int RenderObj::putVert(float x, float y, float z) {
		
		if (vertices.putVec(x, y, z) == NULL)
			return 0;

		return 1;
	}
	
	// Place data into the buffer
	void RenderObj::updateVertBuffer() {

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.getSize(), vertices.ptr(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, vertSize, GL_FLOAT, GL_TRUE, stride, 0);
		glEnableVertexAttribArray(0);
		//glGetBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * vertCount, temp);

	}

	
	// Constructor
	RenderObj::RenderObj() {

		vertSize = 3;
		stride = sizeof(float) * vertSize;

	}

	RenderObj::RenderObj(int vertSize) {

		RenderObj::vertSize = vertSize;
		stride = sizeof(float) * vertSize;

	}

	// Destructor
	RenderObj::~RenderObj() {

		glDeleteBuffers(1, &vertexBuffer);

	}


}// Namespace PiratesLife
