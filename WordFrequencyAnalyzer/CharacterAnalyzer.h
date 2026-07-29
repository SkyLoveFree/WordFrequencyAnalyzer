#pragma once

#include<unordered_map>

#include<vector>

#include<utility>

#include<cstdint>

#include"UTF8Codec.h"

class CharacterAnalyzer
{
public:
	void analyze(const std::vector<std::uint32_t> codepoints);//统计频率
	void pirntFrequency();//打印频率，未排序
private:
	std::unordered_map<uint32_t, int> frequency;

	std::vector<std::pair<uint32_t, int>> sortedFrequency;

	UTF8Codec codec;
	bool shouldIgnore(uint32_t c);
};