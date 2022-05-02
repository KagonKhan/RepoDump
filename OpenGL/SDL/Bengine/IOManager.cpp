#include "IOManager.h"
#include <fstream>

bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {

	std::ifstream file(filePath, std::ios::binary);
	if (file.fail()) {
		perror(filePath.c_str());
		return false;
	}

	//Seek to the end of file
	file.seekg(0, std::ios::end);

	//get filesize
	int fileSize = file.tellg();

	file.seekg(0, std::ios::beg);
	fileSize -= file.tellg();

	buffer.resize(fileSize);

	file.read((char*)&buffer[0], fileSize);
	file.close();




	return true;
}
