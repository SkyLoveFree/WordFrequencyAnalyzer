#include"TextAnalyzer.h"
#include<iostream>
#include<algorithm>
#include<cctype>


bool TextAnalyzer::shouldIgnore(char c)
{
	return std::isspace(c);
}

void TextAnalyzer::analyze(const std::string& text)
{
	for (auto s : text)
	{
		if(!shouldIgnore(s))frequency[s]++;
	}
}

void TextAnalyzer::printFrequency()
{
	for (auto& pair : frequency)
	{
		std::cout << pair.first << ":" << pair.second<<std::endl;
	}
}

std::vector<std::pair<char, int>> TextAnalyzer::getSortedFrequency()
{
	sortedFrequency.assign(frequency.begin(), frequency.end());

	std::sort(sortedFrequency.begin(),sortedFrequency.end(),
		[](auto& a,auto& b)
	{
		if(a.second!=b.second)return a.second > b.second;
		else return a.first<b.first;
	});
	return sortedFrequency;
}

void TextAnalyzer::pirntSortedFrequency()
{
	for (auto& p:sortedFrequency)
	{
		std::cout << p.first << ": " << p.second << std::endl;
	}
}

