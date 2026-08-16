#include"TextAnalyzer.h"
namespace WFA
{

void TextAnalyzer::analyzeChar(const std::string& str)
{
	auto codepoints = UTF8Codec::decode(str);

	m_CharacterAnalyzer.analyze(codepoints);
}



SearchResult TextAnalyzer::search(const std::string& text, const std::string& target)
{
	return m_TextSearcher.search(text, target);
}

std::vector<std::string> TextAnalyzer::getContexts(const SearchResult& result,ContextConfig config)
{
	return m_TextSearcher.getContexts(result,config);
}

}//namespace WFA