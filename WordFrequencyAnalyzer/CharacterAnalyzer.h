#pragma once

#include<unordered_map>

#include<vector>

#include<utility>

#include"UTF8Codec.h"

class CharacterAnalyzer
{
public:
	void analyze(const std::vector<char32_t> codepoints);//统计频率
	void pirntFrequency();//打印频率，未排序
private:
	std::unordered_map<char32_t, int> frequency;

	std::vector<std::pair<char32_t, int>> sortedFrequency;

	UTF8Codec codec;
	bool shouldIgnore(char32_t c);
};