

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
			int putVert(float i);

			// Constructor
			RenderObj();

			// Deconstructor
			~RenderObj();

		private:
			float *verts;
			int maxVerts;
			int vertCount;
			unsigned int vertexBuffer;

	};

} // namespace PiratesLife

#endif // RENDEROBJ_H_
