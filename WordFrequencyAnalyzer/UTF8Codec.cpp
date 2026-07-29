#include"UTF8Codec.h"

#include"utf8.h"

bool UTF8Codec::shouldIgnore(uint32_t c)
{
	return c == 0x0020 || c == 0x0009 || c == 0x000A || c == 0x000D
		|| c == 0x00A0   // 不间断空格
		|| c == 0x3000;  // 全角空格
}
std::vector<uint32_t> UTF8Codec::decode(const std::string& input_text)
{
	std::vector<uint32_t> codepoints;
	utf8::utf8to32(input_text.begin(), input_text.end(), std::back_inserter(codepoints));
	return codepoints;
}

std::string UTF8Codec::encode(const uint32_t& cp)
{
	std::string result;
	utf8::append(cp, std::back_inserter(result));
	return result;
}

