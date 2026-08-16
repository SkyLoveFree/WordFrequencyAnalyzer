#pragma once

#include"UTF8Codec.h"
#include"CharacterAnalyzer.h"
#include"TextSearcher.h"

namespace WFA
{
	
class TextAnalyzer
{
private:
	CharacterAnalyzer m_CharacterAnalyzer;
	TextSearcher m_TextSearcher;
public:

	void analyzeChar(const std::string& str);
	SearchResult search(const std::string& text, const std::string& target);//搜索，
	//得到指定词汇的出现次数和位置，结果包含了text_decode和target_decode，避免重复解码
	std::vector<std::string> getContexts(const SearchResult& result, ContextConfig config = {});
	//获得所有指定词汇的上下文，可自定义范围,依赖search函数返回的SearchResult，避免重复解码
};

}//namespace WFA