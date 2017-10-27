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

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, vertSize, GL_FLOAT, GL_FALSE, stride, 0);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);

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
		int i = 0;
		float *tempArr = NULL;

		// Check if verts needs to be expanded
		if (vertCount > (maxVerts * 3) / 4) {

			maxVerts *= 2;
			tempArr = new float[maxVerts];

			if (tempArr == NULL)
				return -1;

			for (i = 0; i < vertCount; i++) {

				tempArr[i] = verts[i];

			}

			delete[] verts;
			verts = tempArr;

		}

		verts[vertCount] = x;
		vertCount++;

		verts[vertCount] = y;
		vertCount++;

		verts[vertCount] = z;
		vertCount++;

		return 0;
	}
	
	// Place data into the buffer
	void RenderObj::updateVertBuffer() {

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertCount, verts, GL_STATIC_DRAW);
		glVertexAttribPointer(0, vertSize, GL_FLOAT, GL_FALSE, stride, 0);
		glEnableVertexAttribArray(0);

	}

	
	// Constructor
	RenderObj::RenderObj() {

		vertCount = 0;
		maxVerts = 20;
		vertSize = 3;
		stride = sizeof(float) * vertSize;
		verts = new float[maxVerts];

	}

	RenderObj::RenderObj(int vertSize) {

		vertCount = 0;
		maxVerts = 20;
		RenderObj::vertSize = vertSize;
		stride = sizeof(float) * vertSize;
		verts = new float[maxVerts];

	}

	// Destructor
	RenderObj::~RenderObj() {

		glDeleteBuffers(1, &vertexBuffer);

	}


}// Namespace PiratesLife
