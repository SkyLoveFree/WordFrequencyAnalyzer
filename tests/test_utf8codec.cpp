// Tests for UTF8Codec: the byte <-> codepoint contract.
//
// All non-ASCII input is written as explicit hex byte sequences and expected
// values as explicit codepoints. This keeps the test source pure ASCII so it
// compiles identically regardless of source-file encoding (a real trap on
// MSVC + Chinese Windows, where UTF-8 source without a BOM is read as GBK).

#include "UTF8Codec.h"
#include "test_framework.h"

#include <stdexcept>
#include <string>
#include <vector>

using WFA::UTF8Codec;

TEST_CASE("decode ASCII: one codepoint per byte")
{
    auto cps = UTF8Codec::decode("hello");
    CHECK_CPVEC_EQ(cps, (std::vector<char32_t>{'h', 'e', 'l', 'l', 'o'}));
}

TEST_CASE("decode empty string gives empty vector")
{
    CHECK(UTF8Codec::decode("").empty());
}

TEST_CASE("decode 2-byte and 3-byte sequences (Chinese)")
{
    // "你好" = U+4F60 U+597D = E4 BD A0 / E5 A5 BD
    std::string input("\xE4\xBD\xA0\xE5\xA5\xBD");
    auto cps = UTF8Codec::decode(input);
    CHECK_CPVEC_EQ(cps, (std::vector<char32_t>{0x4F60, 0x597D}));
}

TEST_CASE("decode 4-byte sequence (emoji)")
{
    // "😀" = U+1F600 = F0 9F 98 80
    std::string input("\xF0\x9F\x98\x80");
    CHECK_CPVEC_EQ(UTF8Codec::decode(input), (std::vector<char32_t>{0x1F600}));
}

TEST_CASE("decode rejects a lone continuation byte")
{
    // 0x80 has the continuation-byte shape but no lead byte before it.
    CHECK_THROWS(UTF8Codec::decode(std::string("\x80")), std::runtime_error);
}

TEST_CASE("decode rejects a truncated sequence")
{
    // 你 = E4 BD A0; stop after two bytes -> incomplete 3-byte sequence.
    CHECK_THROWS(UTF8Codec::decode(std::string("\xE4\xBD")), std::runtime_error);
}

TEST_CASE("decode rejects a surrogate encoded in UTF-8")
{
    // U+D800 is a UTF-16 surrogate, illegal to encode directly in UTF-8.
    CHECK_THROWS(UTF8Codec::decode(std::string("\xED\xA0\x80")), std::runtime_error);
}

TEST_CASE("encode single codepoint")
{
    // 你 = U+4F60 = E4 BD A0
    CHECK_EQ(UTF8Codec::encode(char32_t(0x4F60)), std::string("\xE4\xBD\xA0"));
}

TEST_CASE("encode vector of mixed widths")
{
    // 你(U+4F60, 3 bytes) 好(U+597D, 3 bytes) 😀(U+1F600, 4 bytes)
    std::vector<char32_t> cps{0x4F60, 0x597D, 0x1F600};
    CHECK_EQ(UTF8Codec::encode(cps),
             std::string("\xE4\xBD\xA0\xE5\xA5\xBD\xF0\x9F\x98\x80"));
}

TEST_CASE("decode then encode is the identity")
{
    std::string original("\xE4\xBD\xA0\xE5\xA5\xBD"); // 你好
    CHECK_EQ(UTF8Codec::encode(UTF8Codec::decode(original)), original);
}
