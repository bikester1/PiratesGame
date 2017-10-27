

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
			void putVert(float i);

			// Constructor
			RenderObj();

			// Deconstructor
			~RenderObj();

		private:
			float verts[6];
			int vertCount;
			unsigned int vertexBuffer;

	};

} // namespace PiratesLife

#endif // RENDEROBJ_H_
