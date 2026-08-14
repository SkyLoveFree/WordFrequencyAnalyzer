#include"TextSearcher.h"

SearchResult TextSearcher::search(const std::string& text,const std::string& target)//搜索，得到指定词汇的出现次数和位置
{
	SearchResult result;
	auto text_decode = UTF8Codec::decode(text);
	auto target_decode = UTF8Codec::decode(target);
	size_t m = text_decode.size(), n = target_decode.size();
	result.text_decode = text_decode;
	result.target_decode = target_decode;
	if (n > m) return result;
	for (size_t i = 0;i <= m - n;++i)//0-m-n
	{
		bool match = true;
		for (size_t j = 0;j < n;++j)
		{
			if (text_decode[i + j] != target_decode[j])
			{
				match = false;
				break;
			}
		}
		if (match)
		{
			result.count++;
			result.positions.push_back(i);
			i += n-1;//跳过已经匹配的部分，因为循环会自动加1，所以这里减1
		}
	}
	return result;
}
//获取所有匹配位置的上下文，使用SearchResult作为参数，避免重复解码，result中包含了text_decode和target_decode，由search函数返回。
std::vector<std::string> TextSearcher::getContexts(const SearchResult& result, ContextConfig config)
{
	std::vector<std::string> contexts;
	size_t max=result.text_decode.size();
	for(size_t i=0;i<result.positions.size();++i)
	{
		size_t pos=result.positions[i];
		size_t start=pos<config.before?0:pos-config.before;
		size_t end=pos+result.target_decode.size()+config.after>=max?max:pos+result.target_decode.size()+config.after;//[start,end)
		std::vector<char32_t> context(result.text_decode.begin()+start,result.text_decode.begin()+end);
		contexts.push_back(UTF8Codec::encode(context));
	}
	return contexts;
}