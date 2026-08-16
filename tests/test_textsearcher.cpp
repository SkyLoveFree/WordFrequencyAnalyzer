// Tests for TextSearcher::search and ::getContexts (plus one facade check).
//
// Two non-obvious behaviours are pinned down here so a future refactor cannot
// silently change them:
//   * positions are codepoint indices, not byte offsets (important for CJK);
//   * matching is non-overlapping: "aaa" matches "aaaa" once, not twice.

#include "TextSearcher.h"
#include "TextAnalyzer.h"
#include "test_framework.h"

#include <string>
#include <vector>

using WFA::TextSearcher;
using WFA::SearchResult;
using WFA::ContextConfig;

TEST_CASE("search returns every occurrence with codepoint positions")
{
    TextSearcher searcher;
    SearchResult r = searcher.search("hello world hello", "hello");
    CHECK_EQ(r.count, 2u);
    CHECK_EQ(r.positions.size(), 2u);
    CHECK_EQ(r.positions[0], 0u);
    CHECK_EQ(r.positions[1], 12u);
}

TEST_CASE("search returns empty result when target is absent")
{
    TextSearcher searcher;
    SearchResult r = searcher.search("hello", "xyz");
    CHECK_EQ(r.count, 0u);
    CHECK(r.positions.empty());
}

TEST_CASE("search with empty target is safe")
{
    // Regression: empty target used to underflow size_t (n-1) and loop forever.
    TextSearcher searcher;
    SearchResult r = searcher.search("hello", "");
    CHECK_EQ(r.count, 0u);
    CHECK(r.positions.empty());
}

TEST_CASE("search with target longer than text is safe")
{
    TextSearcher searcher;
    SearchResult r = searcher.search("ab", "abcd");
    CHECK_EQ(r.count, 0u);
    CHECK(r.positions.empty());
}

TEST_CASE("search is non-overlapping")
{
    TextSearcher searcher;
    SearchResult r = searcher.search("aaaa", "aaa");
    CHECK_EQ(r.count, 1u);
    CHECK_EQ(r.positions.size(), 1u);
    CHECK_EQ(r.positions[0], 0u);
}

TEST_CASE("search positions are codepoint indices, not byte offsets")
{
    // "你好世界你好" is 6 codepoints (18 bytes); "你好" sits at indices 0 and 4.
    TextSearcher searcher;
    SearchResult r = searcher.search(
        std::string("\xE4\xBD\xA0\xE5\xA5\xBD\xE4\xB8\x96\xE7\x95\x8C"
                    "\xE4\xBD\xA0\xE5\xA5\xBD"),
        std::string("\xE4\xBD\xA0\xE5\xA5\xBD"));
    CHECK_EQ(r.count, 2u);
    CHECK_EQ(r.positions[0], 0u);
    CHECK_EQ(r.positions[1], 4u);
}

TEST_CASE("getContexts returns the whole text when range exceeds bounds")
{
    TextSearcher searcher;
    SearchResult r = searcher.search("hello world", "world"); // index 6
    auto ctxs = searcher.getContexts(r); // default before=10, after=10
    CHECK_EQ(ctxs.size(), 1u);
    CHECK_EQ(ctxs[0], std::string("hello world"));
}

TEST_CASE("getContexts honours custom before/after")
{
    TextSearcher searcher;
    SearchResult r = searcher.search("hello world", "world"); // index 6
    ContextConfig cfg{2, 2};
    auto ctxs = searcher.getContexts(r, cfg);
    CHECK_EQ(ctxs[0], std::string("o world")); // indices [4, 11)
}

TEST_CASE("getContexts clamps start at the beginning of text")
{
    TextSearcher searcher;
    SearchResult r = searcher.search("abcdef", "a"); // index 0
    ContextConfig cfg{10, 1};
    auto ctxs = searcher.getContexts(r, cfg);
    CHECK_EQ(ctxs[0], std::string("ab")); // [0, 2)
}

TEST_CASE("getContexts clamps end at the end of text")
{
    TextSearcher searcher;
    SearchResult r = searcher.search("abcdef", "f"); // index 5
    ContextConfig cfg{1, 10};
    auto ctxs = searcher.getContexts(r, cfg);
    CHECK_EQ(ctxs[0], std::string("ef")); // [4, 6)
}

TEST_CASE("TextAnalyzer facade wires search end to end")
{
    WFA::TextAnalyzer analyzer;
    SearchResult r = analyzer.search("hello world hello", "hello");
    CHECK_EQ(r.count, 2u);
}
