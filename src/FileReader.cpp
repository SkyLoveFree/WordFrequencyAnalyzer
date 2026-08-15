#include"FileReader.h"

#include <stdexcept>

#include<fstream>

#include<iterator>

std::string FileReader::readFile(const std::string& Filename)
{
	std::ifstream file(Filename,std::ios::binary);
	if (!file.is_open())
	{
		throw std::runtime_error(
			"无法打开文件" + Filename
		);
	}
	return std::string(
		std::istreambuf_iterator<char>(file),
		std::istreambuf_iterator<char>()
	);
}