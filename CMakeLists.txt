cmake_minimum_required(VERSION 3.10)

project(WordFrequencyAnalyzer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/bin
)


add_executable(
    WordFrequencyAnalyzer

    src/main.cpp
    src/UTF8Codec.cpp
    src/FileReader.cpp
    src/CharacterAnalyzer.cpp
    src/TextAnalyzer.cpp
    src/TextSearcher.cpp
)


target_include_directories(
    WordFrequencyAnalyzer
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/third_party/utf8
)