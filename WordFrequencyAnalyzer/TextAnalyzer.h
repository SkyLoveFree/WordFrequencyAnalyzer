#pragma once

#include<string>

#include<unordered_map>

#include<vector>

#include<utility>

#include<cstdint>

class TextAnalyzer
{
public:
	void analyze(const std::string& text);//统计频率
	void printFrequency();//打印频率，未排序

	std::vector<std::pair<uint32_t, int>> getSortedFrequency();//得到已经排好序的频率
	void pirntSortedFrequency();//打印频率，已经排序
private:
	std::string cp_to_utf8(uint32_t cp);//cp->utf-8

	std::unordered_map<uint32_t, int> frequency;

	std::vector<std::pair<uint32_t, int>> sortedFrequency;

	bool shouldIgnore(uint32_t c);//屏蔽一些不需要统计的东西

};