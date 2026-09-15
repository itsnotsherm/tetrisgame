#pragma once

#include <array>
#include <iostream>

inline constexpr int BOARD_WIDTH = 10;
inline constexpr int BOARD_HEIGHT = 20;

enum class Cell { Empty, Filled };

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
