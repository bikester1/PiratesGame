#include "Importer.h"
#include "ManagedArray.h"

#include <fstream>
#include <iostream>

#include <glm/glm.hpp>

namespace PiratesLife {

	vertexBufferRetStruct *Importer::ImportVerticesFromOBJ(std::string filePath) {
		std::string line;
		std::ifstream fileStream(filePath.c_str(), std::ios::in);
		ManagedArray<glm::vec3> vertArr = ManagedArray<glm::vec3>();
		ManagedArray<glm::vec3> faceArr = ManagedArray<glm::vec3>();
		float *retFloat;
		vertexBufferRetStruct *retStruct;
		int i;

		glm::vec3 tempVec;

		if (fileStream.is_open()) {
			while (getline(fileStream, line)) {
				std::string::size_type index = 0;

				if (line[0] == '#') 
					continue;
				else if (line[0] == 'v') {
					tempVec.x = std::stof(line.substr(1), &index);
					tempVec.y = std::stof(line.substr(index), &index);
					tempVec.z = std::stof(line.substr(index));

					vertArr.putVec(tempVec);
				}
				else if (line[0] == 'f') {
					faceArr.putVec(vertArr.getVec(std::stoi(line.substr(1), &index)));
					faceArr.putVec(vertArr.getVec(std::stoi(line.substr(index), &index)));
					faceArr.putVec(vertArr.getVec(std::stoi(line.substr(index))));
				}
			}
		}

		return NULL;
	}

	Importer::Importer()
	{
	}


	Importer::~Importer()
	{
	}

}