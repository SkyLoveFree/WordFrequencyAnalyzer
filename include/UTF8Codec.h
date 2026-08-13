#pragma once
#include <cstdint>
#include<string>
#include<vector>

class UTF8Codec
{
public:
	static std::vector<char32_t> decode(const std::string& input_text);
	static std::string encode(const char32_t& cp);
	
private:
		bool shouldIgnore(char32_t c);//屏蔽一些不需要统计的东西
};