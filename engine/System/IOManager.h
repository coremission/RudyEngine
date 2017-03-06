#ifndef IOMANAGER_h
#define IOMANAGER_h

#include <string>
#include <vector>

class IOManager
{
public:
	static bool readBinaryFileToBuffer(std::string filePath, std::vector<unsigned char>& outBuffer);
};

#endif //IOMANAGER_h