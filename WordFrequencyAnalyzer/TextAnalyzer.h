#pragma once

#include<string>

#include<unordered_map>

class TextAnalyzer
{
public:
	void analyze(const std::string& text);//统计频率
	void printFrequency();
private:
	std::unordered_map<char, int> frequency;
};