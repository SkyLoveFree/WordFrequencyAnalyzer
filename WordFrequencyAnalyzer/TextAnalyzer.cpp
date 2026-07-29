#include"TextAnalyzer.h"

void TextAnalyzer::analyzeChar(const std::string& str)
{
	auto codepoints = UTF8Codec.decode(str);

	CharacterAnalyzer.analyze(codepoints);
}

void TextAnalyzer::printCharFrequency()
{
	CharacterAnalyzer.pirntFrequency();
}