#include"CharacterAnalyzer.h"
#include<iostream>
#include<algorithm>

void CharacterAnalyzer::analyze(const std::vector<char32_t> codepoints)
{
	for (auto cp : codepoints)
	{
		if (shouldIgnore(cp)) continue;
		frequency[cp]++;
	}
	sortedFrequency.assign(
		frequency.begin(),
		frequency.end()
	);
	std::sort(sortedFrequency.begin(), sortedFrequency.end(),
		[](const auto& a, const auto& b)
		{
			if (a.second != b.second)return a.second > b.second;
			else return a.first < b.first;
		});
}
void CharacterAnalyzer::pirntFrequency()
{
	for (auto& p :sortedFrequency)
	{
		std::cout << codec.encode(p.first)
				  << ":"
				  << p.second
				  << std::endl;
	}
}
bool CharacterAnalyzer::shouldIgnore(char32_t c)
{
	return c == 0x0020 || c == 0x0009 || c == 0x000A || c == 0x000D
		|| c == 0x00A0   // 不间断空格
		|| c == 0x3000;  // 全角空格
}
