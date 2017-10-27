

#ifndef RENDEROBJ_H_
#define RENDEROBJ_H_

#include <Vector>

namespace PiratesLife {

	class RenderObj {

		public:
			
			void render();

			// Transfer saved vertices to VBO
			void updateVertBuffer();

			// init opengl
			void initBuffers();

			// getters
			
			// setters
			int putVert(float x, float y, float z);

			// Constructor
			RenderObj();
			RenderObj(int vertSize);

			// Deconstructor
			~RenderObj();

		private:
			float* verts;
			int maxVerts;
			int vertCount;
			unsigned int vertexBuffer;

			// how many floats are in one vertex
			int vertSize;

			// how far apart are each vertex
			int stride;
	};

} // namespace PiratesLife

#endif // RENDEROBJ_H_
