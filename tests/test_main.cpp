#include "test_framework.h"

// Entry point for the test executable. `run_all()` executes every TEST_CASE
// registered across all translation units and returns 0 iff all pass.
int main() {
    return wfa_test::run_all();
}
