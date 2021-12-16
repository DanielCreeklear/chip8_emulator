#include "utils.h"

bool loadFile(const char* fileName, std::stringstream& result)
{
	try
	{
		std::ifstream file;

		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		file.open(fileName);
		result << file.rdbuf();
		file.close();

		return true;
	}
	catch (std::exception except)
	{
		std::cerr << "[ERROR] " << except.what() << " : " << fileName << std::endl;
	}

	return false;
}