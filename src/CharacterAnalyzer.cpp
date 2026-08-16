#include"CharacterAnalyzer.h"
#include<iostream>
#include<algorithm>

namespace WFA {

std::unordered_map<char32_t, size_t> CharacterAnalyzer::analyze(const std::vector<char32_t>& codepoints)
{
	std::unordered_map<char32_t, size_t> frequency;
	for (auto cp : codepoints)
	{
		if (shouldIgnore(cp)) continue;
		frequency[cp]++;
	}
	return frequency;
}

bool CharacterAnalyzer::shouldIgnore(char32_t c)
{
	return c == 0x0020 || c == 0x0009 || c == 0x000A || c == 0x000D
		|| c == 0x00A0   // 不间断空格
		|| c == 0x3000;  // 全角空格
}
}//namespace WFA