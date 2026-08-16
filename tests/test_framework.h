#pragma once
// Minimal single-header test harness, written specifically for this project.
//
// Why not Catch2 / doctest / gtest? Two reasons:
//   1. They are external dependencies; on a Chinese-Windows setup downloading
//      them adds friction for no benefit at this scale.
//   2. The machinery is the lesson. A test is just a registered function; a
//      failure is just a thrown exception. Making that visible is more valuable
//      for learning than hiding it behind a mature framework's macros.

#include <cstdint>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace wfa_test {

// Thrown by a failing CHECK; carries the "file:line, what failed, values" text.
struct TestFailure : std::runtime_error {
    explicit TestFailure(const std::string& msg) : std::runtime_error(msg) {}
};

struct TestCase {
    std::string name;
    std::function<void()> fn;
};

// All test cases live in one process-wide registry. `inline` guarantees there
// is a single instance even though this header is included by many .cpp files.
inline std::vector<TestCase>& registry() {
    static std::vector<TestCase> cases;
    return cases;
}

// Each TEST_CASE creates one Registrar whose constructor self-registers.
struct Registrar {
    Registrar(const std::string& name, std::function<void()> fn) {
        registry().push_back(TestCase{name, std::move(fn)});
    }
};

inline int& assertion_count() {
    static int n = 0;
    return n;
}

// Renders codepoints as "U+4F60" so a mismatch is readable instead of showing
// raw integers or unprintable characters.
inline std::string format_codepoints(const std::vector<char32_t>& cps) {
    std::ostringstream os;
    os << "[" << cps.size() << " codepoints:";
    for (char32_t cp : cps) {
        os << " U+" << std::hex << static_cast<std::uint32_t>(cp) << std::dec;
    }
    os << " ]";
    return os.str();
}

// Runs every registered test, prints PASS/FAIL, returns 0 iff all pass.
inline int run_all() {
    int passed = 0;
    for (const TestCase& tc : registry()) {
        try {
            tc.fn();
            std::cout << "[PASS] " << tc.name << "\n";
            ++passed;
        } catch (const std::exception& e) {
            std::cout << "[FAIL] " << tc.name << "\n       " << e.what() << "\n";
        } catch (...) {
            std::cout << "[FAIL] " << tc.name << "\n       (non-standard exception)\n";
        }
    }
    std::cout << "\n" << passed << "/" << registry().size()
              << " test cases passed (" << assertion_count() << " assertions checked)\n";
    return (passed == static_cast<int>(registry().size())) ? 0 : 1;
}

} // namespace wfa_test

#define WFA_TEST_STR_IMPL(x) #x
#define WFA_TEST_STR(x) WFA_TEST_STR_IMPL(x)
#define WFA_TEST_CAT_IMPL(a, b) a##b
#define WFA_TEST_CAT(a, b) WFA_TEST_CAT_IMPL(a, b)

// TEST_CASE("name") { ... }  -> declares a static function, registers it, then
// lets you define the body. `__LINE__` keeps names unique within a file.
#define TEST_CASE(name)                                                     \
    static void WFA_TEST_CAT(wfa_test_fn_, __LINE__)();                     \
    static ::wfa_test::Registrar WFA_TEST_CAT(wfa_test_reg_, __LINE__)(     \
        name, WFA_TEST_CAT(wfa_test_fn_, __LINE__));                        \
    static void WFA_TEST_CAT(wfa_test_fn_, __LINE__)()

#define CHECK(cond)                                                         \
    do {                                                                    \
        ++::wfa_test::assertion_count();                                    \
        if (!(cond)) {                                                      \
            throw ::wfa_test::TestFailure(                                  \
                std::string(__FILE__) + ":" + WFA_TEST_STR(__LINE__) +      \
                " CHECK failed: " #cond);                                   \
        }                                                                   \
    } while (0)

#define CHECK_FALSE(cond) CHECK(!(cond))

#define CHECK_EQ(a, b)                                                      \
    do {                                                                    \
        ++::wfa_test::assertion_count();                                    \
        const auto& wfa_va = (a);                                           \
        const auto& wfa_vb = (b);                                           \
        if (!(wfa_va == wfa_vb)) {                                          \
            std::ostringstream wfa_os;                                      \
            wfa_os << __FILE__ << ":" << __LINE__ << " CHECK_EQ failed\n"   \
                   << "    " << #a << " == " << #b << "\n"                  \
                   << "    left  = " << wfa_va << "\n"                      \
                   << "    right = " << wfa_vb;                             \
            throw ::wfa_test::TestFailure(wfa_os.str());                    \
        }                                                                   \
    } while (0)

#define CHECK_THROWS(expr, ex_type)                                         \
    do {                                                                    \
        ++::wfa_test::assertion_count();                                    \
        bool wfa_threw = false;                                             \
        try {                                                               \
            (void)(expr);                                                   \
        } catch (const ex_type&) {                                          \
            wfa_threw = true;                                               \
        }                                                                   \
        if (!wfa_threw) {                                                   \
            throw ::wfa_test::TestFailure(                                  \
                std::string(__FILE__) + ":" + WFA_TEST_STR(__LINE__) +      \
                " CHECK_THROWS failed: expected " #ex_type " to be thrown");\
        }                                                                   \
    } while (0)

// Compares two vector<char32_t> and prints both as codepoints on failure.
#define CHECK_CPVEC_EQ(actual, expected)                                    \
    do {                                                                    \
        ++::wfa_test::assertion_count();                                    \
        const auto& wfa_va = (actual);                                      \
        const auto& wfa_ve = (expected);                                    \
        if (!(wfa_va == wfa_ve)) {                                          \
            throw ::wfa_test::TestFailure(                                  \
                std::string(__FILE__) + ":" + WFA_TEST_STR(__LINE__) +      \
                " codepoints mismatch\n    actual:   " +                    \
                ::wfa_test::format_codepoints(wfa_va) +                     \
                "\n    expected: " + ::wfa_test::format_codepoints(wfa_ve));\
        }                                                                   \
    } while (0)
