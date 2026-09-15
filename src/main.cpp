#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

#include "Board.h"
#include "Game.h"

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
