#pragma once

#include <clocale>

#include <ncurses.h>

#include "Board.h"
#include "Game.h"

inline constexpr int INPUT_POLL_MS = 10;
inline constexpr int CELL_WIDTH = 2;
inline constexpr int BOARD_TOP = 1;
inline constexpr int BOARD_LEFT = 2;

class Terminal {
public:
    Terminal() {
        std::setlocale(LC_ALL, "");
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        curs_set(0);
        timeout(INPUT_POLL_MS);
    }

    ~Terminal() { endwin(); }

    Terminal(const Terminal&) = delete;
    Terminal& operator=(const Terminal&) = delete;

    int readKey() const { return getch(); }

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

        mvaddstr(BOARD_TOP, BOARD_LEFT, "┌");
        mvaddstr(BOARD_TOP, right, "┐");
        mvaddstr(bottom, BOARD_LEFT, "└");
        mvaddstr(bottom, right, "┘");

        for (int x = 0; x < inner_width; ++x) {
            mvaddstr(BOARD_TOP, BOARD_LEFT + 1 + x, "-");
            mvaddstr(bottom, BOARD_LEFT + 1 + x, "─");
        }

        for (int y = 0; y < BOARD_HEIGHT; ++y) {
            mvaddstr(BOARD_TOP + 1 + y, BOARD_LEFT, "│");
            mvaddstr(BOARD_TOP + 1 + y, right, "│");
        }
    }
};
