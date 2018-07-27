

#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "day10.h"
#include "main.h"

using namespace std;

class Day10Test : public ::testing::Test{};

TEST( Day10Test, Part1and2_1 ) {
    std::string input(
        "value 5 goes to bot 2\n"
        "bot 2 gives low to bot 1 and high to bot 0\n"
        "value 3 goes to bot 1\n"
        "bot 1 gives low to output 1 and high to bot 0\n"
        "bot 0 gives low to output 2 and high to output 0\n"
        "value 2 goes to bot 2\n"
        );
    std::istringstream is( input );

    unsigned valuesBot;
    unsigned product012;

    SimulateBots( is, 2U, 5U, valuesBot, product012 );

    EXPECT_EQ( 2, valuesBot );
    EXPECT_EQ( 30, product012 );
}

TEST(Day10Test, PuzzleInputPart1 ) {
    ifstream is( "day10.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "161\n", os.str() );
}

TEST(Day10Test, PuzzleInputPart2 ) {
    ifstream is( "day10.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "133163\n", os.str() );
}
