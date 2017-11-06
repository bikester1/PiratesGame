

#ifndef RENDEROBJ_H_
#define RENDEROBJ_H_

#include "ManagedArray.h"
#include "Camera.h"

#include <Vector>
#include <fstream>
#include <iostream>
#include <string>

#include <glm/vec3.hpp>

namespace PiratesLife {

	class RenderObj {

		public:
			
			void render();
			
			// import obj file into myVertices
			void importOBJ(std::string filePath);

			// Transfer saved vertices to VBO
			void updateVertBuffer();

			// init opengl
			void initBuffers();

			// getters
			float getPosX();

			float getPosY();

			float getPosZ();

			glm::vec3 getPos(float x, float y, float z);

			glm::mat4x4 getMVP();


			// setters
			int putVert(float x, float y, float z);

			void setPosX(float x);

			void setPosY(float y);

			void setPosZ(float z);

			void setScale(glm::vec3 scale);

			void setPos(float x, float y, float z);

			void loadTexture(std::string filePath, std::vector<float> *textureArray);

			void setProgram(unsigned int program);

			// Constructor
			RenderObj();
			RenderObj(int vertSize);
			RenderObj(PiratesLife::Camera *cam);

			// Deconstructor
			~RenderObj();

		private:
			//ManagedArray<glm::vec3> myVertices;
			unsigned int vertexBuffer;
			unsigned int MVPMatrix;
			unsigned int modelMatrix;
			unsigned int viewMatrix;
			unsigned int program;
			unsigned int textureBuffer;
			glm::vec3 pos;
			glm::vec3 rot;
			glm::vec3 scale;
			std::vector<glm::vec3> myVertices;
			std::vector<float> myTexture;
			PiratesLife::Camera *cam;
			bool hasNormals;
			bool hasTexture;

			GLvoid** vertexAttribOffset;
			GLvoid** normalAttribOffset;
			GLvoid** textureAttribOffset;

			// how many floats are in one vertex
			int vertSize;
			int numOfVertices;

			// how far apart are each vertex
			int stride;
	};

} // namespace PiratesLife

#endif // RENDEROBJ_H_
