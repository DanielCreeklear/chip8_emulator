#include "utils.h"

bool loadFile(std::string *fileName, std::stringstream& result)
{
	try
	{
		std::ifstream file;
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		file.open(fileName->c_str());
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