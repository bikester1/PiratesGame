

#ifndef RENDEROBJ_H_
#define RENDEROBJ_H_

#include <Vector>
#include "managedArray.h"
#include "Camera.h"
#include <glm/vec3.hpp>

namespace PiratesLife {

	class RenderObj {

		public:
			
			void render();

			// Transfer saved vertices to VBO
			void updateVertBuffer();

			// init opengl
			void initBuffers();

			// getters
			float getPosX(float x);

			float getPosY(float y);

			float getPosZ(float z);

			glm::vec3 getPos(float x, float y, float z);

			glm::mat4x4 getMVP();


			// setters
			int putVert(float x, float y, float z);

			void setPosX(float x);

			void setPosY(float y);

			void setPosZ(float z);

			void setPos(float x, float y, float z);

			// Constructor
			RenderObj();
			RenderObj(int vertSize);
			RenderObj(PiratesLife::Camera *cam);

			// Deconstructor
			~RenderObj();

		private:
			managedArray<glm::vec3> myVertices;
			unsigned int vertexBuffer;
			glm::vec3 pos;
			glm::vec3 rot;
			glm::vec3 scale;
			PiratesLife::Camera *cam;

			// how many floats are in one vertex
			int vertSize;

			// how far apart are each vertex
			int stride;
	};

} // namespace PiratesLife

#endif // RENDEROBJ_H_
