#pragma once

#include<unordered_map>

#include<vector>

#include<utility>

#include"UTF8Codec.h"
namespace WFA{
class CharacterAnalyzer
{
public:
	std::unordered_map<char32_t, size_t> analyze(const std::vector<char32_t>& codepoints);//分析，返回字符的码素平吕
private:

	UTF8Codec codec;
	bool shouldIgnore(char32_t c);
};
}//namespace WFA