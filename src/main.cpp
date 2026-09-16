#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

#include <iostream>

#include "Game.h"

void simulateLineClear() {
    Board board;

    for (int column = 0; column < BOARD_WIDTH; ++column) {
        const Piece vertical_i{PieceType::I, {column - 2, BOARD_HEIGHT - 4}, 1};
        lock(board, vertical_i);
    }

    std::cout << "10 vertical I pieces locked\n";
    board.print();
    std::cout << '\n';

    board.clearFullLines();
    std::cout << "after clearFullLines\n";
    board.print();
    std::cout << '\n';
}

void simulateMoves() {
    Game game;

    auto show = [&game](const char* label) {
        std::cout << label << '\n';
        game.print();
        std::cout << '\n';
    };

    show("spawned");

    game.moveLeft();
    game.moveLeft();
    game.moveLeft();
    show("moved left 3");

    game.rotate();
    show("rotated");

    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        game.tick();
    }
    show("after 20 ticks: first piece locked, next piece falling");

    int ticks = 0;
    while (!game.isGameOver() && ticks < 10000) {
        game.tick();
        ++ticks;
    }

    std::cout << "game over: " << std::boolalpha << game.isGameOver() << " after " << ticks
              << " more ticks\n";
    game.print();
}

int main(int argc, char** argv) {
    doctest::Context context(argc, argv);
    const int test_result = context.run();
    if (context.shouldExit() || test_result != 0) {
        return test_result;
    }

    simulateLineClear();
    simulateMoves();

    return 0;
}
