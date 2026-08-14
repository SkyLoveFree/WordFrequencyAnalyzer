#include "FileReader.h"
#include "TextAnalyzer.h"

#include <iostream>


int main()
{
    try
    {
        FileReader reader;

        std::string str = reader.readFile(
            R"(C:\Users\Sky\Desktop\vscode\WordFrequencyAnalyzer\tests\test.text)"
        );


        TextAnalyzer analyzer;


        // 测试搜索
        SearchResult result = analyzer.search(str, "你好");


        std::cout << "count: "
                  << result.count
                  << std::endl;


        std::cout << "positions:" << std::endl;

        for(auto pos : result.positions)
        {
            std::cout << pos << " ";
        }

        std::cout << std::endl;



        // 测试上下文
        ContextConfig config;

        config.before = 5;
        config.after = 5;


        auto contexts = analyzer.getContexts(
            result,
            config
        );


        std::cout << "\ncontexts:\n";

        for(const auto& context : contexts)
        {
            std::cout << context << std::endl;
        }


    }
    catch(std::exception& e)
    {
        std::cout << e.what();
    }


    return 0;
}