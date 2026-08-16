cmake_minimum_required(VERSION 3.10)

project(WordFrequencyAnalyzer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/bin
)


# ---------------------------------------------------------------------------
# Core library: everything except the CLI entry point.
# Splitting this out lets the test executable link the exact same code as the
# application, instead of re-listing (and riskily duplicating) the source files.
# ---------------------------------------------------------------------------
add_library(
    WFA_core STATIC

    src/UTF8Codec.cpp
    src/FileReader.cpp
    src/CharacterAnalyzer.cpp
    src/TextAnalyzer.cpp
    src/TextSearcher.cpp
)

target_include_directories(
    WFA_core
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/third_party/utf8
)


add_executable(
    WordFrequencyAnalyzer

    src/main.cpp
)

target_link_libraries(WordFrequencyAnalyzer PRIVATE WFA_core)


# ---------------------------------------------------------------------------
# Compiler warnings
# ---------------------------------------------------------------------------
function(wfa_enable_warnings target)
    if (MSVC)
        # /EHsc: enable standard C++ exception handling. Without it, the
        # `throw` in FileReader/UTF8Codec and the test framework's try/catch
        # compile with warning C4530 and do not unwind correctly.
        target_compile_options(${target} PRIVATE /W4 /EHsc)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endfunction()

wfa_enable_warnings(WFA_core)
wfa_enable_warnings(WordFrequencyAnalyzer)


# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------
enable_testing()

add_executable(
    WFA_tests

    tests/test_main.cpp
    tests/test_utf8codec.cpp
    tests/test_filereader.cpp
    tests/test_characteranalyzer.cpp
    tests/test_textsearcher.cpp
)

target_link_libraries(WFA_tests PRIVATE WFA_core)
target_include_directories(WFA_tests PRIVATE ${PROJECT_SOURCE_DIR}/tests)
wfa_enable_warnings(WFA_tests)

add_test(NAME WFA_tests COMMAND WFA_tests)
