cmake_minimum_required(VERSION 3.20)
project(tetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# doctest: unit-testing library, downloaded on first configure.
include(FetchContent)
FetchContent_Declare(doctest
    URL https://github.com/doctest/doctest/archive/refs/tags/v2.4.11.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(doctest)

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)

add_executable(tetris src/main.cpp)
target_include_directories(tetris PRIVATE ${CURSES_INCLUDE_DIRS})
target_link_libraries(tetris PRIVATE doctest::doctest ${CURSES_LIBRARIES})
target_compile_options(tetris PRIVATE -Wall -Wextra -Wpedantic)

# `ctest` runs the executable in tests-only mode.
enable_testing()
add_test(NAME tetris_tests COMMAND tetris --exit)
