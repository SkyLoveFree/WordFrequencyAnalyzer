#include"UTF8Codec.h"

#include"utf8.h"

bool UTF8Codec::shouldIgnore(char32_t c)
{
	return c == 0x0020 || c == 0x0009 || c == 0x000A || c == 0x000D
		|| c == 0x00A0   // 不间断空格
		|| c == 0x3000;  // 全角空格
}
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

