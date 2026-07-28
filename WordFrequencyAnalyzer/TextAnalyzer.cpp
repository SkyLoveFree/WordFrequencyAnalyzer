#include"TextAnalyzer.h"
#include<iostream>
#include<algorithm>
#include<cctype>
#include"utf8.h"



bool TextAnalyzer::shouldIgnore(uint32_t c)
{
	return c == 0x0020 || c == 0x0009 || c == 0x000A || c == 0x000D
		|| c == 0x00A0   // 不间断空格
		|| c == 0x3000;  // 全角空格
}

void TextAnalyzer::analyze(const std::string& text)
{
	std::vector<uint32_t> codepoints;
	utf8::utf8to32(text.begin(), text.end(),std::back_inserter(codepoints));

	for (auto cp : codepoints)
	{
		if(!shouldIgnore(cp))frequency[cp]++;
	}
}

void TextAnalyzer::printFrequency()
{
	for (auto& pair : frequency)
	{
		std::cout << cp_to_utf8(pair.first) << ":" << pair.second<<std::endl;
	}
}

std::vector<std::pair<uint32_t, int>> TextAnalyzer::getSortedFrequency()
{
	sortedFrequency.assign(frequency.begin(), frequency.end());

	std::sort(sortedFrequency.begin(),sortedFrequency.end(),
		[](const auto& a,const auto& b)
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
		std::cout << cp_to_utf8(p.first) << ": " << p.second << std::endl;
	}
}

std::string TextAnalyzer::cp_to_utf8(uint32_t cp)
{
	std::string result;
	utf8::append(cp, std::back_inserter(result));
	return result;
} 