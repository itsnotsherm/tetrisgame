#include <array>

#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

constexpr int kBoardWidth = 10;
constexpr int kBoardHeight = 20;

enum class Cell { Empty, Filled };

class Board {
public:
    bool isInside(int x, int y) const {
        return x >= 0 && x < kBoardWidth && y >= 0 && y < kBoardHeight;
    }

    Cell get(int x, int y) const { return cells_.at(y).at(x); }
    void set(int x, int y, Cell cell) { cells_.at(y).at(x) = cell; }

private:
    std::array<std::array<Cell, kBoardWidth>, kBoardHeight> cells_{};
};

int main(int argc, char** argv) {
    doctest::Context context(argc, argv);
    const int testResult = context.run();
    if (context.shouldExit() || testResult != 0) {
        return testResult;
    }

    return 0;
}
