#pragma once

#include<string>

#include<unordered_map>

#include<vector>

#include<utility>

class TextAnalyzer
{
public:
	void analyze(const std::string& text);//统计频率
	void printFrequency();//打印频率，未排序

	std::vector<std::pair<char, int>> getSortedFrequency();//得到已经排好序的频率
	void pirntSortedFrequency();//打印频率，已经排序
private:
	std::unordered_map<char, int> frequency;

	std::vector<std::pair<char, int>> sortedFrequency;

	bool shouldIgnore(char c);//屏蔽一些不需要统计的东西
};