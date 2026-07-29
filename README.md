一个简单的通过c++实现检测文本中词语出现次数的简单软件，也是我真正要落地的第一款软件。
A simple C++ text Words  frequency analyzer project

This project uses [utfcpp](https://github.com/nemtrif/utfcpp) for UTF-8 encoding and decoding support.

Thanks to the developers of utfcpp for providing this excellent library.

V0.1.0
just a demo
can read text and output frequency
i will do more

v0.1.1
能够识别并统计出ASCII码内范围的字符频率，并可以从高到低输出，但遇到ASCII码外的字符会产生bug
下一步的计划是实现utf-8的转化，让程序不会读到一些特殊字符就崩溃。

Can identify and count character frequencies within the ASCII range, and output them in descending order.
However, encountering characters outside the ASCII range causes bugs.

Next step:​
Implement UTF-8 decoding so that the program does not crash when reading special characters.

v0.2.0

支持识别utf-8了，感谢utfcpp,下一步计划开始实现输出词语的输出频率。

support utf-8 thanks utfcpp

v0.2.1

今天重新优化了结构，将类拆分的更细，更贴近低耦合，让代码更健壮，让我能够更轻松的添加新的功能。原来是直接在TextAnalyzer里面写utf的解码译码，还有统计单字符的平吕，很不方便我在后续增加分词，词语频率的统计，并且随着代码量的上升，我越来越难修改一个代码量庞大的文件，在拆分后，让增加新的功能变得越来越简单。

下一步打算增添分词模块和词语频率统计模块，先准备实现简单的英语分词，英语天生比其他语言好分词，通过符号，空格等就能作到，很适合我这个新手来干。

Today I reorganized the structure, splitting classes into finer granularity to achieve lower coupling and make the code more robust, which allows me to add new features with ease. Previously, UTF decoding/encoding and single-character frequency counting were all written directly inside TextAnalyzer, making it very inconvenient to later add tokenization or word frequency statistics. As the codebase grew larger, modifying a single huge file became increasingly difficult. After refactoring, adding new functionality has become much simpler.
Next step: I plan to implement a tokenization module and a word frequency statistics module. First, I'll start with simple English tokenization — English is inherently easier to split than other languages (using spaces, punctuation, etc.), which makes it a perfect starting point for a beginner like me.