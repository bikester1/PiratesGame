#pragma once
#include <String>

namespace PiratesLife {

	struct vertexBufferRetStruct {
		int length;
		float **vertices;
	};

	class Importer
	{
	public:

		vertexBufferRetStruct *Importer::ImportVerticesFromOBJ(std::string filePath);

		Importer();

		~Importer();

	};

}
