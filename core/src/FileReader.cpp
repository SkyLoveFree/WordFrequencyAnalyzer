#include"FileReader.h"

#include <stdexcept>

#include<fstream>

#include<iterator>

namespace SkyReader
{
	std::string FileReader::readFile(const std::string& Filename)
{
	std::ifstream file(Filename,std::ios::binary);
	if (!file.is_open())
	{
		throw std::runtime_error(
			"无法打开文件" + Filename
		);
	}
	std::string content{
		std::istreambuf_iterator<char>(file),
		std::istreambuf_iterator<char>()
	};
	const std::string BOM = "\xEF\xBB\xBF";
	if (content.starts_with(BOM))
		content.erase(0, BOM.size());//解决BOM出现在开头，进入解码。
	return content;  
}

}//namespace SkyReader

