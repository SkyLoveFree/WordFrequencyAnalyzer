#include"FileReader.h"

#include <stdexcept>

#include<fstream>

std::string FileReader::readFile(const std::string& Filename)
{
	std::ifstream file(Filename);
	if (!file.is_open())
	{
		throw std::runtime_error(
			"无法打开文件" + Filename
		);
	}
	std::string text;
	std::string line;
	while (std::getline(file, line))
	{
		text += line;
		text += '\n';
	}
	return text;
}