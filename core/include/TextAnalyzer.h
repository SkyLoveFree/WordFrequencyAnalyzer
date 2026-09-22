#pragma once

#include"UTF8Codec.h"
#include"CharacterAnalyzer.h"
#include"TextSearcher.h"
#include"FileReader.h"

namespace SkyReader
{
	
class TextAnalyzer
{
private:
	CharacterAnalyzer m_CharacterAnalyzer;
	TextSearcher m_TextSearcher;
	FileReader m_FileReader;

	std::string m_text;
public:
	void loadFile(const std::string& Filename);//读取文件，输入文件路径
	void analyzeChar(const std::string& str);
	SearchResult search(const std::string& target);//搜索，
	//得到指定词汇的出现次数和位置，结果包含了text_decode和target_decode，避免重复解码
	std::vector<std::string> getContexts(const SearchResult& result, ContextConfig config = {});
	//获得所有指定词汇的上下文，可自定义范围,依赖search函数返回的SearchResult，避免重复解码
	std::string getContext(
		const SearchResult& result,
		size_t occurrence,
		ContextConfig config = {}
    );//获得指定词汇指定出现次数的上下文)
};
}//namespace SkyReader