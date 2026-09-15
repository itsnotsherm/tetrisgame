#pragma once

#include <array>
#include <stdexcept>

enum class PieceType { I, O, T, S, Z, J, L };

inline constexpr int PIECE_TYPE_COUNT = 7;

struct Point {
    int x;
    int y;
};

using Shape = std::array<Point, 4>;

// ....  ..#.  ....  .#..
// ####  ..#.  ....  .#..
// ....  ..#.  ####  .#..
// ....  ..#.  ....  .#..
inline constexpr std::array<Shape, 4> I_ROTATIONS = {{
    {{ {0, 1}, {1, 1}, {2, 1}, {3, 1} }},
    {{ {2, 0}, {2, 1}, {2, 2}, {2, 3} }},
    {{ {0, 2}, {1, 2}, {2, 2}, {3, 2} }},
    {{ {1, 0}, {1, 1}, {1, 2}, {1, 3} }},
}};

// .##.  .##.  .##.  .##.
// .##.  .##.  .##.  .##.
inline constexpr std::array<Shape, 4> O_ROTATIONS = {{
    {{ {1, 0}, {2, 0}, {1, 1}, {2, 1} }},
    {{ {1, 0}, {2, 0}, {1, 1}, {2, 1} }},
    {{ {1, 0}, {2, 0}, {1, 1}, {2, 1} }},
    {{ {1, 0}, {2, 0}, {1, 1}, {2, 1} }},
}};

// .#.  .#.  ...  .#.
// ###  .##  ###  ##.
// ...  .#.  .#.  .#.
inline constexpr std::array<Shape, 4> T_ROTATIONS = {{
    {{ {1, 0}, {0, 1}, {1, 1}, {2, 1} }},
    {{ {1, 0}, {1, 1}, {2, 1}, {1, 2} }},
    {{ {0, 1}, {1, 1}, {2, 1}, {1, 2} }},
    {{ {1, 0}, {0, 1}, {1, 1}, {1, 2} }},
}};

// .##  .#.  ...  #..
// ##.  .##  .##  ##.
// ...  ..#  ##.  .#.
inline constexpr std::array<Shape, 4> S_ROTATIONS = {{
    {{ {1, 0}, {2, 0}, {0, 1}, {1, 1} }},
    {{ {1, 0}, {1, 1}, {2, 1}, {2, 2} }},
    {{ {1, 1}, {2, 1}, {0, 2}, {1, 2} }},
    {{ {0, 0}, {0, 1}, {1, 1}, {1, 2} }},
}};

// ##.  ..#  ...  .#.
// .##  .##  ##.  ##.
// ...  .#.  .##  #..
inline constexpr std::array<Shape, 4> Z_ROTATIONS = {{
    {{ {0, 0}, {1, 0}, {1, 1}, {2, 1} }},
    {{ {2, 0}, {1, 1}, {2, 1}, {1, 2} }},
    {{ {0, 1}, {1, 1}, {1, 2}, {2, 2} }},
    {{ {1, 0}, {0, 1}, {1, 1}, {0, 2} }},
}};

// #..  .##  ...  .#.
// ###  .#.  ###  .#.
// ...  .#.  ..#  ##.
inline constexpr std::array<Shape, 4> J_ROTATIONS = {{
    {{ {0, 0}, {0, 1}, {1, 1}, {2, 1} }},
    {{ {1, 0}, {2, 0}, {1, 1}, {1, 2} }},
    {{ {0, 1}, {1, 1}, {2, 1}, {2, 2} }},
    {{ {1, 0}, {1, 1}, {0, 2}, {1, 2} }},
}};

// ..#  .#.  ...  ##.
// ###  .#.  ###  .#.
// ...  .##  #..  .#.
inline constexpr std::array<Shape, 4> L_ROTATIONS = {{
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

inline const std::array<Shape, 4>& rotationsOf(PieceType type) {
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

inline const Shape& shapeOf(const Piece& piece) {
    return rotationsOf(piece.type)[piece.rotation];
}

inline Shape cellsOf(const Piece& piece) {
    Shape cells = shapeOf(piece);
    for (Point& cell : cells) {
        cell.x += piece.position.x;
        cell.y += piece.position.y;
    }
    return cells;
}
