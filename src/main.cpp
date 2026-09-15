// We provide our own main() instead of letting doctest generate one,
// so tests and game can live in the same file.
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

constexpr int kBoardWidth = 10;
constexpr int kBoardHeight = 20;

// Game code and TEST_CASEs go here.

int main(int argc, char** argv) {
    // Run all TEST_CASEs first. Pass --exit to run only the tests, --no-run to skip them.
    doctest::Context context(argc, argv);
    const int testResult = context.run();
    if (context.shouldExit() || testResult != 0) {
        return testResult;
    }

    return 0;
}
