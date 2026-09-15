#include <array>
#include <iostream>
#include <random>
#include <stdexcept>

#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

constexpr int BOARD_WIDTH = 10;
constexpr int BOARD_HEIGHT = 20;

enum class Cell { Empty, Filled };

enum class PieceType { I, O, T, S, Z, J, L };

constexpr int PIECE_TYPE_COUNT = 7;

struct Point {
    int x;
    int y;
};

constexpr Point SPAWN_POSITION{3, 0};

using Shape = std::array<Point, 4>;

// ....  ..#.  ....  .#..
// ####  ..#.  ....  .#..
// ....  ..#.  ####  .#..
// ....  ..#.  ....  .#..
constexpr std::array<Shape, 4> I_ROTATIONS = {{
    {{ {0, 1}, {1, 1}, {2, 1}, {3, 1} }},
    {{ {2, 0}, {2, 1}, {2, 2}, {2, 3} }},
    {{ {0, 2}, {1, 2}, {2, 2}, {3, 2} }},
    {{ {1, 0}, {1, 1}, {1, 2}, {1, 3} }},
}};

// .##.  .##.  .##.  .##.
// .##.  .##.  .##.  .##.
constexpr std::array<Shape, 4> O_ROTATIONS = {{
    {{ {1, 0}, {2, 0}, {1, 1}, {2, 1} }},
    {{ {1, 0}, {2, 0}, {1, 1}, {2, 1} }},
    {{ {1, 0}, {2, 0}, {1, 1}, {2, 1} }},
    {{ {1, 0}, {2, 0}, {1, 1}, {2, 1} }},
}};

// .#.  .#.  ...  .#.
// ###  .##  ###  ##.
// ...  .#.  .#.  .#.
constexpr std::array<Shape, 4> T_ROTATIONS = {{
    {{ {1, 0}, {0, 1}, {1, 1}, {2, 1} }},
    {{ {1, 0}, {1, 1}, {2, 1}, {1, 2} }},
    {{ {0, 1}, {1, 1}, {2, 1}, {1, 2} }},
    {{ {1, 0}, {0, 1}, {1, 1}, {1, 2} }},
}};

// .##  .#.  ...  #..
// ##.  .##  .##  ##.
// ...  ..#  ##.  .#.
constexpr std::array<Shape, 4> S_ROTATIONS = {{
    {{ {1, 0}, {2, 0}, {0, 1}, {1, 1} }},
    {{ {1, 0}, {1, 1}, {2, 1}, {2, 2} }},
    {{ {1, 1}, {2, 1}, {0, 2}, {1, 2} }},
    {{ {0, 0}, {0, 1}, {1, 1}, {1, 2} }},
}};

// ##.  ..#  ...  .#.
// .##  .##  ##.  ##.
// ...  .#.  .##  #..
constexpr std::array<Shape, 4> Z_ROTATIONS = {{
    {{ {0, 0}, {1, 0}, {1, 1}, {2, 1} }},
    {{ {2, 0}, {1, 1}, {2, 1}, {1, 2} }},
    {{ {0, 1}, {1, 1}, {1, 2}, {2, 2} }},
    {{ {1, 0}, {0, 1}, {1, 1}, {0, 2} }},
}};

// #..  .##  ...  .#.
// ###  .#.  ###  .#.
// ...  .#.  ..#  ##.
constexpr std::array<Shape, 4> J_ROTATIONS = {{
    {{ {0, 0}, {0, 1}, {1, 1}, {2, 1} }},
    {{ {1, 0}, {2, 0}, {1, 1}, {1, 2} }},
    {{ {0, 1}, {1, 1}, {2, 1}, {2, 2} }},
    {{ {1, 0}, {1, 1}, {0, 2}, {1, 2} }},
}};

// ..#  .#.  ...  ##.
// ###  .#.  ###  .#.
// ...  .##  #..  .#.
constexpr std::array<Shape, 4> L_ROTATIONS = {{
    {{ {2, 0}, {0, 1}, {1, 1}, {2, 1} }},
    {{ {1, 0}, {1, 1}, {1, 2}, {2, 2} }},
    {{ {0, 1}, {1, 1}, {2, 1}, {0, 2} }},
    {{ {0, 0}, {1, 0}, {1, 1}, {1, 2} }},
}};

struct Piece {
    PieceType type;
    Point position;
    int rotation;
};

const std::array<Shape, 4>& rotationsOf(PieceType type) {
    switch (type) {
        case PieceType::I: return I_ROTATIONS;
        case PieceType::O: return O_ROTATIONS;
        case PieceType::T: return T_ROTATIONS;
        case PieceType::S: return S_ROTATIONS;
        case PieceType::Z: return Z_ROTATIONS;
        case PieceType::J: return J_ROTATIONS;
        case PieceType::L: return L_ROTATIONS;
    }
    throw std::invalid_argument("unknown piece type");
}

const Shape& shapeOf(const Piece& piece) {
    return rotationsOf(piece.type)[piece.rotation];
}

Shape cellsOf(const Piece& piece) {
    Shape cells = shapeOf(piece);
    for (Point& cell : cells) {
        cell.x += piece.position.x;
        cell.y += piece.position.y;
    }
    return cells;
}

class Board {
public:
    bool isInside(int x, int y) const {
        return x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT;
    }

    Cell get(int x, int y) const { return m_cells.at(y).at(x); }
    void set(int x, int y, Cell cell) { m_cells.at(y).at(x) = cell; }

    void print() const {
        for (int y = 0; y < BOARD_HEIGHT; ++y) {
            for (int x = 0; x < BOARD_WIDTH; ++x) {
                std::cout << (get(x, y) == Cell::Filled ? '#' : '.');
            }
            std::cout << '\n';
        }
    }

private:
    std::array<std::array<Cell, BOARD_WIDTH>, BOARD_HEIGHT> m_cells{};
};

bool fits(const Board& board, const Piece& piece) {
    for (const Point& cell : cellsOf(piece)) {
        if (!board.isInside(cell.x, cell.y) || board.get(cell.x, cell.y) != Cell::Empty) {
            return false;
        }
    }
    return true;
}

void lock(Board& board, const Piece& piece) {
    for (const Point& cell : cellsOf(piece)) {
        board.set(cell.x, cell.y, Cell::Filled);
    }
}

class Game {
public:
    Game() { spawnPiece(); }

    void tick() {
        Piece moved_down = m_current_piece;
        ++moved_down.position.y;
        if (fits(m_board, moved_down)) {
            m_current_piece = moved_down;
        } else {
            lock(m_board, m_current_piece);
            spawnPiece();
        }
    }

private:
    void spawnPiece() {
        std::uniform_int_distribution<int> distribution(0, PIECE_TYPE_COUNT - 1);
        const auto type = static_cast<PieceType>(distribution(m_random_engine));
        m_current_piece = Piece{type, SPAWN_POSITION, 0};
    }

    Board m_board;
    std::mt19937 m_random_engine{std::random_device{}()};
    Piece m_current_piece{};
};

int main(int argc, char** argv) {
    doctest::Context context(argc, argv);
    const int test_result = context.run();
    if (context.shouldExit() || test_result != 0) {
        return test_result;
    }

    Board board;
    board.print();

    return 0;
}
