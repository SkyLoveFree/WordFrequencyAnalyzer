#pragma once

#include"UTF8Codec.h"
#include"CharacterAnalyzer.h"

class TextAnalyzer
{
private:
	UTF8Codec UTF8Codec;
	CharacterAnalyzer CharacterAnalyzer;
public:

	void analyzeChar(const std::string& str);
	void printCharFrequency();
};