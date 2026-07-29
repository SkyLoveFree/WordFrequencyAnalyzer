#pragma once
#include <cstdint>
#include<string>
#include<vector>

class UTF8Codec
{
public:
	std::vector<uint32_t> decode(const std::string& input_text);
	std::string encode(const uint32_t& cp);
	
private:
		bool shouldIgnore(uint32_t c);//屏蔽一些不需要统计的东西
};