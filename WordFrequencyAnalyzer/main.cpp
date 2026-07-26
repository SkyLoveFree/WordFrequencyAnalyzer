#include"FileReader.h"

#include"TextAnalyzer.h"

#include<iostream>

int main()
{
	try
	{
		FileReader reader;
		std::string str = reader.readFile(R"(C:\Users\Sky\source\repos\WordFrequencyAnalyzer\WordFrequencyAnalyzer\test.text)");
		std::cout << str << std::endl;
		TextAnalyzer analyzer;
		analyzer.analyze(str);
		analyzer.printFrequency();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}

}