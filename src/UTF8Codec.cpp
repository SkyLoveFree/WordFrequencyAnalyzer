#include"UTF8Codec.h"

#include"utf8.h"


std::vector<char32_t> UTF8Codec::decode(const std::string& input_text)
{
	std::vector<char32_t> codepoints;
	utf8::utf8to32(input_text.begin(), input_text.end(), std::back_inserter(codepoints));
	return codepoints;
}

std::string UTF8Codec::encode(const char32_t& cp)
{
	std::string result;
	utf8::append(cp, std::back_inserter(result));
	return result;
}

std::string UTF8Codec::encode(const std::vector<char32_t>& codepoints)
{
	std::string result;
	result.reserve(codepoints.size() * 4); // 预分配内存，避免多次分配
	for(const auto&cp:codepoints)
	{
		utf8::append(cp,std::back_inserter(result));
	}
	return result;
}

