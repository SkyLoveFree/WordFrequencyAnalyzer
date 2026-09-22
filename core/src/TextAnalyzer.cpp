#include"TextAnalyzer.h"
namespace SkyReader
{

void TextAnalyzer::analyzeChar(const std::string& str)
{
	auto codepoints = UTF8Codec::decode(str);

	m_CharacterAnalyzer.analyze(codepoints);
}



SearchResult TextAnalyzer::search(const std::string& target)
{
	return m_TextSearcher.search(m_text, target);
}

std::vector<std::string> TextAnalyzer::getContexts(const SearchResult& result,ContextConfig config)
{
	return m_TextSearcher.getContexts(result,config);
}

std::string TextAnalyzer::getContext(const SearchResult& result,
	size_t occurrence,
	ContextConfig config )
{
    return m_TextSearcher.getContext(result,occurrence,config);
}


void TextAnalyzer::loadFile(const std::string& Filename)
{
	m_text = m_FileReader.readFile(Filename);
}
}//namesapce SkyReader