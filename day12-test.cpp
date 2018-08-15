#include <gtest/gtest.h>
#include <fstream>
#include <list>
#include <iostream>
#include <sstream>
#include <string>

#include "day11.h"
#include "main.h"

using namespace std;

class Day12Test : public ::testing::Test{};

TEST( Day12Test, Part1DescriptionTest ) {
    std::istringstream is(
        "cpy 41 a\n"
        "inc a\n"
        "inc a\n"
        "dec a\n"
        "jnz a 2\n"
        "dec a\n"
    );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "42\n", os.str() );
}

TEST(Day12Test, PuzzleInputPart1 ) {
    ifstream is( "day12.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "318007\n", os.str() );
}

TEST(Day12Test, PuzzleInputPart2 ) {
    ifstream is( "day12.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "9227661\n", os.str() );
}
