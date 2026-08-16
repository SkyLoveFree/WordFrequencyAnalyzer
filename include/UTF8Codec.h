#pragma once
#include <cstdint>
#include<string>
#include<vector>
namespace WFA
{	

class UTF8Codec
{
public:
	static std::vector<char32_t> decode(const std::string& input_text);
	static std::string encode(const char32_t& cp);
	static std::string encode(const std::vector<char32_t>&codepoints);
	

};

}//namespace WFA