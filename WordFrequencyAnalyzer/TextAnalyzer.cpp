#include"TextAnalyzer.h"
#include<iostream>

void TextAnalyzer::analyze(const std::string& text)
{
	for (auto s : text)
	{
		frequency[s]++;
	}
}

void TextAnalyzer::printFrequency()
{
	for (auto& pair : frequency)
	{
		std::cout << pair.first << ":" << pair.second<<std::endl;
	}
}