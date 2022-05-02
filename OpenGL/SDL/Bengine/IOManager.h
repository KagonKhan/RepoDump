#pragma once

#include <vector>
#include <string>

class IOManager {
	IOManager() = delete;
	~IOManager() = delete;


public:

	static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);





};

