#include "IOManager.h"

#include <string>
#include <fstream>

bool IOManager::readBinaryFileToBuffer(std::string filePath, std::vector<unsigned char>& outBuffer)
{
	std::ifstream file(filePath, std::ios::binary);

	if(file.fail()) {
		perror(filePath.c_str());
		return false;
	}

	file.seekg(0, std::ios::end);

	unsigned int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);


	fileSize -= file.tellg();

	outBuffer.resize(fileSize);

	file.read(reinterpret_cast<char *>(&outBuffer[0]), fileSize);
	file.close();

	return true;
}
