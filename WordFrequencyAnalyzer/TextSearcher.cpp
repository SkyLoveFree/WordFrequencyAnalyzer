#include"TextSearcher.h"

int TextSearcher::countOccurrences(const std::string& text,const std::string& target)
{
	auto text_decode = UTF8Codec::decode(text);
	auto target_decode = UTF8Codec::decode(target);
	int count = 0;
	int m = text_decode.size(), n = target_decode.size();
	if (n > m) return 0;
	for (size_t i = 0;i <= m - n;++i)//0-m-n
	{
		bool match = true;
		for (size_t j = 0;j < n;++j)
		{
			if (text_decode[i + j] != target_decode[j])
			{
				match = false;
				break;
			}
		}
		if (match)
		{
			count++;
			i += n;
		}
	}
	return count;
}