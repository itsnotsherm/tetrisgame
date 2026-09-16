#pragma once

#include <ncurses.h>

#include "Board.h"
#include "Game.h"

inline constexpr int CELL_WIDTH = 2;
inline constexpr int BOARD_TOP = 1;
inline constexpr int BOARD_LEFT = 2;

class Terminal {
public:
    Terminal() {
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        curs_set(0);
    }

    ~Terminal() { endwin(); }

    Terminal(const Terminal&) = delete;
    Terminal& operator=(const Terminal&) = delete;

    void draw(const Game& game) const {
        erase();
        drawBorder();

        const Board view = game.view();
        for (int y = 0; y < BOARD_HEIGHT; ++y) {
            for (int x = 0; x < BOARD_WIDTH; ++x) {
                const char* cell = view.get(x, y) == Cell::Filled ? "[]" : "  ";
                mvaddstr(BOARD_TOP + 1 + y, BOARD_LEFT + 1 + x * CELL_WIDTH, cell);
            }
        }

        refresh();
    }

private:
    void drawBorder() const {
        const int inner_width = BOARD_WIDTH * CELL_WIDTH;
        const int right = BOARD_LEFT + inner_width + 1;
        const int bottom = BOARD_TOP + BOARD_HEIGHT + 1;

        mvaddch(BOARD_TOP, BOARD_LEFT, ACS_ULCORNER);
        mvaddch(BOARD_TOP, right, ACS_URCORNER);
        mvaddch(bottom, BOARD_LEFT, ACS_LLCORNER);
        mvaddch(bottom, right, ACS_LRCORNER);
        mvhline(BOARD_TOP, BOARD_LEFT + 1, ACS_HLINE, inner_width);
        mvhline(bottom, BOARD_LEFT + 1, ACS_HLINE, inner_width);
        mvvline(BOARD_TOP + 1, BOARD_LEFT, ACS_VLINE, BOARD_HEIGHT);
        mvvline(BOARD_TOP + 1, right, ACS_VLINE, BOARD_HEIGHT);
    }
};
