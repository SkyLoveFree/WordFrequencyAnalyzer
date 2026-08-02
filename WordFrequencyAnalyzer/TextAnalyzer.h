#pragma once

#include"UTF8Codec.h"
#include"CharacterAnalyzer.h"
#include"TextSearcher.h"


class TextAnalyzer
{
private:
	CharacterAnalyzer CharacterAnalyzer;
	TextSearcher TextSearcher;
public:

	void analyzeChar(const std::string& str);
	void printCharFrequency();
	int StringOccurrences(const std::string& text, const std::string& target);
};