#pragma once
#include<string>
namespace SkyReader
{
	class FileReader
	{
	public:

	std::string readFile(const std::string& Filename);//input: file path, output: file content
	};
}
