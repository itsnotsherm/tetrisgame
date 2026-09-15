#include <array>

#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

constexpr int kBoardWidth = 10;
constexpr int kBoardHeight = 20;

enum class Cell { Empty, Filled };

enum class PieceType { I, O, T, S, Z, J, L };

struct Point {
    int x;
    int y;
};

using Shape = std::array<Point, 4>;

constexpr std::array<Shape, 4> kTRotations = {{
    {{ {1, 0}, {0, 1}, {1, 1}, {2, 1} }},
    {{ {1, 0}, {1, 1}, {2, 1}, {1, 2} }},
    {{ {0, 1}, {1, 1}, {2, 1}, {1, 2} }},
    {{ {1, 0}, {0, 1}, {1, 1}, {1, 2} }},
}};

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
