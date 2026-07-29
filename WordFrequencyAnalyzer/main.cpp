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
		analyzer.analyzeChar(str);
		analyzer.printCharFrequency();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}

}