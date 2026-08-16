// Tests for CharacterAnalyzer::analyze.
//
// The contract under test: given decoded codepoints, return a frequency map,
// ignoring whitespace. analyze() is pure (it builds a fresh map each call and
// does not read member state), which makes these tests deterministic.

#include "CharacterAnalyzer.h"
#include "test_framework.h"

#include <cstddef>
#include <unordered_map>
#include <vector>

using WFA::CharacterAnalyzer;

namespace {

// Returns 0 for an absent key instead of throwing like map.at(), so a missing
// character fails the assertion with a clear message rather than an exception.
std::size_t freq_of(const std::unordered_map<char32_t, std::size_t>& m,
                    char32_t key) {
    auto it = m.find(key);
    return it == m.end() ? 0 : it->second;
}

} // namespace

TEST_CASE("analyze empty input gives empty map")
{
    CharacterAnalyzer analyzer;
    auto freq = analyzer.analyze(std::vector<char32_t>{});
    CHECK(freq.empty());
}

TEST_CASE("analyze counts repeated characters")
{
    CharacterAnalyzer analyzer;
    auto freq = analyzer.analyze(std::vector<char32_t>{'a', 'b', 'a'});
    CHECK_EQ(freq.size(), 2u);
    CHECK_EQ(freq_of(freq, 'a'), 2u);
    CHECK_EQ(freq_of(freq, 'b'), 1u);
}

TEST_CASE("analyze is case-sensitive")
{
    CharacterAnalyzer analyzer;
    auto freq = analyzer.analyze(std::vector<char32_t>{'A', 'a'});
    CHECK_EQ(freq_of(freq, 'A'), 1u);
    CHECK_EQ(freq_of(freq, 'a'), 1u);
}

TEST_CASE("analyze ignores all whitespace kinds")
{
    CharacterAnalyzer analyzer;
    // space, tab, LF, CR, NBSP(U+00A0), full-width space(U+3000)
    auto freq = analyzer.analyze(std::vector<char32_t>{
        'a', ' ', '\t', '\n', '\r', 0x00A0, 0x3000, 'b'});
    CHECK_EQ(freq.size(), 2u); // only 'a' and 'b' survive
    CHECK_EQ(freq_of(freq, 'a'), 1u);
    CHECK_EQ(freq_of(freq, 'b'), 1u);
}

TEST_CASE("analyze counts multi-byte characters")
{
    CharacterAnalyzer analyzer;
    // 你好你 = U+4F60 U+597D U+4F60
    auto freq = analyzer.analyze(std::vector<char32_t>{0x4F60, 0x597D, 0x4F60});
    CHECK_EQ(freq_of(freq, 0x4F60), 2u);
    CHECK_EQ(freq_of(freq, 0x597D), 1u);
}
