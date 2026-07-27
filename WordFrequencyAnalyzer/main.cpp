#include"FileReader.h"

#include"TextAnalyzer.h"

#include<iostream>

int main()
{
	try
	{
		FileReader reader;
		std::string str = reader.readFile(R"(C:\Users\Sky\source\repos\WordFrequencyAnalyzer\WordFrequencyAnalyzer\test.text)");
		TextAnalyzer analyzer;
		analyzer.analyze(str);
		analyzer.getSortedFrequency();
		analyzer.pirntSortedFrequency();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}

}