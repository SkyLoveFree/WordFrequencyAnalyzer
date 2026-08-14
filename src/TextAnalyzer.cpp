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

SearchResult TextAnalyzer::search(const std::string& text, const std::string& target)
{
	return TextSearcher.search(text, target);
}

std::vector<std::string> TextAnalyzer::getContexts(const SearchResult& result,ContextConfig config)
{
	return TextSearcher.getContexts(result,config);
}