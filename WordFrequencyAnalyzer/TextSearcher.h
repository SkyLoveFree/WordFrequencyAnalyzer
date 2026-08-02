#pragma once
#include"UTF8Codec.h"


class TextSearcher
{
public:
	int countOccurrences(
		const std::string& text,
		const std::string& target
	);
};