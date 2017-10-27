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
	
	//---------//
	// setters //
	//---------//

	// Attempts to add to the verts array
	// Returns 0 on success
	// returns -1 on failure
	int RenderObj::putVert(float n) {
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

			delete verts;
			verts = tempArr;

		}

		verts[vertCount] = n;
		vertCount++;

		return 0;
	}
	
	// Place data into the buffer
	void RenderObj::updateVertBuffer() {

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	}

	
	// Constructor
	RenderObj::RenderObj() {

		vertCount = 0;
		maxVerts = 10;
		verts = new float [maxVerts];

	}

	// Destructor
	RenderObj::~RenderObj() {

		glDeleteBuffers(1, &vertexBuffer);

	}


}// Namespace PiratesLife
