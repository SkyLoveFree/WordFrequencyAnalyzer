// Tests for FileReader::readFile.
//
// FileReader's job is "return the file's bytes exactly as they are on disk".
// The two CRLF / no-trailing-newline cases are regression tests: the previous
// getline-based reader rewrote line endings and appended a phantom '\n', which
// would corrupt search positions and contexts.

#include "FileReader.h"
#include "test_framework.h"

#include <cstdio>
#include <fstream>
#include <string>
#include <utility>

using WFA::FileReader;

namespace {

// RAII helper: writes `content` verbatim to a named file, removes it on
// destruction even if a CHECK fails midway. Binary mode guarantees the bytes on
// disk match `content` exactly (no \n -> \r\n translation on Windows).
struct TempFile {
    std::string path;

    TempFile(std::string name, const std::string& content)
        : path(std::move(name)) {
        std::ofstream out(path, std::ios::out | std::ios::binary);
        out << content;
    }

    ~TempFile() { std::remove(path.c_str()); }
};

} // namespace

TEST_CASE("readFile returns the exact file content")
{
    TempFile f("wfa_fr_normal.txt", "hello world\n");
    FileReader reader;
    CHECK_EQ(reader.readFile(f.path), std::string("hello world\n"));
}

TEST_CASE("readFile preserves CRLF line endings")
{
    // Regression: the old getline reader collapsed "\r\n" into "\n".
    TempFile f("wfa_fr_crlf.txt", "line1\r\nline2\r\n");
    FileReader reader;
    CHECK_EQ(reader.readFile(f.path), std::string("line1\r\nline2\r\n"));
}

TEST_CASE("readFile does not append a trailing newline")
{
    // Regression: the old reader added '\n' to a file that lacked one.
    TempFile f("wfa_fr_noeol.txt", "abc");
    FileReader reader;
    CHECK_EQ(reader.readFile(f.path), std::string("abc"));
}

TEST_CASE("readFile reads an empty file as empty string")
{
    TempFile f("wfa_fr_empty.txt", "");
    FileReader reader;
    CHECK(reader.readFile(f.path).empty());
}

TEST_CASE("readFile preserves raw bytes including NUL and 0xFF")
{
    // A text-mode read would stop at 0x00 or mangle 0xFF; binary mode must not.
    std::string binary("\x00\x01\xFF\xFE", 4);
    TempFile f("wfa_fr_binary.txt", binary);
    FileReader reader;
    CHECK_EQ(reader.readFile(f.path), binary);
}

TEST_CASE("readFile throws when the file does not exist")
{
    FileReader reader;
    CHECK_THROWS(reader.readFile("wfa_fr_no_such_file_9f8e7d.txt"),
                 std::runtime_error);
}
