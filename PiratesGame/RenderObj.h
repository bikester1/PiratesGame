

#ifndef RENDEROBJ_H_
#define RENDEROBJ_H_

#include <Vector>

namespace PiratesLife {

	class RenderObj {
	public:

		void render();

		// Transfer saved vertices to VBO
		void updateVertBuffer();

		// getters
		std::vector <int> getVec();

		// setters
		void putVec(int i);

		// Constructor
		RenderObj();

		// Deconstructor
		virtual ~RenderObj();

	private:
		std::vector <int> vec;
		unsigned int vertexBuffer;
	};


} // namespace PiratesLife

#endif // RENDEROBJ_H_
