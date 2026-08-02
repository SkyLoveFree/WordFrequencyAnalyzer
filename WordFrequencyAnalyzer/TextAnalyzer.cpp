#include"TextAnalyzer.h"

void TextAnalyzer::analyzeChar(const std::string& str)
{
	auto codepoints = UTF8Codec::decode(str);

	CharacterAnalyzer.analyze(codepoints);
}

void TextAnalyzer::printCharFrequency()
{
	CharacterAnalyzer.pirntFrequency();
}

int TextAnalyzer::StringOccurrences(const std::string& text, const std::string& target)
{
	return TextSearcher.countOccurrences(text, target);
}
