#include "Importer.h"
#include <fstream>
#include <iostream>

float **Importer::ImportVerticesFromOBJ(std::string filePath) {
	std::string line;
	std::ifstream fileStream(filePath.c_str(), std::ios::in);
	
	if (fileStream.is_open()) {
		while (getline(fileStream, line)) {

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
