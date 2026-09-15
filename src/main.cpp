#include <array>

#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

constexpr int BOARD_WIDTH = 10;
constexpr int BOARD_HEIGHT = 20;

enum class Cell { Empty, Filled };

enum class PieceType { I, O, T, S, Z, J, L };

struct Point {
    int x;
    int y;
};

using Shape = std::array<Point, 4>;

constexpr std::array<Shape, 4> T_ROTATIONS = {{
    {{ {1, 0}, {0, 1}, {1, 1}, {2, 1} }},
    {{ {1, 0}, {1, 1}, {2, 1}, {1, 2} }},
    {{ {0, 1}, {1, 1}, {2, 1}, {1, 2} }},
    {{ {1, 0}, {0, 1}, {1, 1}, {1, 2} }},
}};

class Board {
public:
    bool isInside(int x, int y) const {
        return x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT;
    }

    Cell get(int x, int y) const { return m_cells.at(y).at(x); }
    void set(int x, int y, Cell cell) { m_cells.at(y).at(x) = cell; }

private:
    std::array<std::array<Cell, BOARD_WIDTH>, BOARD_HEIGHT> m_cells{};
};

int main(int argc, char** argv) {
    doctest::Context context(argc, argv);
    const int test_result = context.run();
    if (context.shouldExit() || test_result != 0) {
        return test_result;
    }

    return 0;
}
