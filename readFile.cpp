#include "readFile.h"

void _ReadFile::readFile(const std::string& pathFile)
{
	std::ifstream ifstr(pathFile, std::ios::binary);

	if (!ifstr.is_open())
		throw std::runtime_error("erro open file");

	std::stringstream buf;

	buf << ifstr.rdbuf();
	neuralNetwokStatus = buf.str();
	ifstr.close();

}

std::string _ReadFile::getNeuralNetwokStatus()
{
	return neuralNetwokStatus;
}
