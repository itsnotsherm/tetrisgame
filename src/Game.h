#pragma once

#include <random>

#include "Board.h"
#include "Piece.h"

inline constexpr Point SPAWN_POSITION{3, 0};

inline bool fits(const Board& board, const Piece& piece) {
    for (const Point& cell : cellsOf(piece)) {
        if (!board.isInside(cell.x, cell.y) || board.get(cell.x, cell.y) != Cell::Empty) {
            return false;
        }
    }
    return true;
}

inline void place(Board& board, const Piece& piece) {
    for (const Point& cell : cellsOf(piece)) {
        board.set(cell.x, cell.y, Cell::Filled);
    }
}

class Game {
public:
    Game() { spawnPiece(); }

    void tick() {
        if (!tryMove(0, 1)) {
            place(m_board, m_current_piece);
            m_board.clearFullLines();
            spawnPiece();
        }
    }

    void moveLeft() { tryMove(-1, 0); }
    void moveRight() { tryMove(1, 0); }

    void rotate() {
        Piece rotated = m_current_piece;
        rotated.rotation = (rotated.rotation + 1) % 4;
        if (fits(m_board, rotated)) {
            m_current_piece = rotated;
        }
    }

    bool isGameOver() const { return m_game_over; }

    Board view() const {
        Board board = m_board;
        place(board, m_current_piece);
        return board;
    }

    void print() const { view().print(); }

private:
    bool tryMove(int dx, int dy) {
        Piece moved = m_current_piece;
        moved.position.x += dx;
        moved.position.y += dy;
        if (!fits(m_board, moved)) {
            return false;
        }
        m_current_piece = moved;
        return true;
    }

    void spawnPiece() {
        std::uniform_int_distribution<int> distribution(0, PIECE_TYPE_COUNT - 1);
        const auto type = static_cast<PieceType>(distribution(m_random_engine));
        m_current_piece = Piece{type, SPAWN_POSITION, 0};
        m_game_over = !fits(m_board, m_current_piece);
    }

    Board m_board;
    std::mt19937 m_random_engine{std::random_device{}()};
    Piece m_current_piece{};
    bool m_game_over = false;
};
