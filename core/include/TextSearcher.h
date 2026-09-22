#pragma once
#include"UTF8Codec.h"
namespace SkyReader
{	

struct SearchResult
{
	size_t count=0;
	std::vector<size_t> positions;

	std::vector<char32_t> text_decode;
	std::vector<char32_t> target_decode;
};

struct ContextConfig
{
	size_t before=10;
	size_t after=10;
};

class TextSearcher
{
public:
	SearchResult search(
		const std::string& text,
		const std::string& target
	);//搜索，得到指定词汇的出现次数和位置
	
	std::vector<std::string> getContexts(
		const SearchResult& result,
		ContextConfig config={}
	);//获得所有指定词汇的上下文，可自定义范围,依赖search函数返回的SearchResult，避免重复解码

	std::string getContext(
		const SearchResult& result,
		size_t occurrence,
		ContextConfig config={}
    );//获得指定词汇指定出现次数的上下文
};

}//namespace SkyReader