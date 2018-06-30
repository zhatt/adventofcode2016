
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>

#include "main.h"

using namespace std;

class Day5Test : public ::testing::Test{};

TEST_F( Day5Test, Part1_1 ) {
    istringstream is( "abc" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "18f47a30\n", os.str() );
}

TEST_F(Day5Test, PuzzleInputPart1 ) {
    ifstream is( "day5.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "1a3099aa\n", os.str() );
}

TEST_F( Day5Test, Part2_1 ) {
    istringstream is( "abc" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "05ace8e3\n", os.str() );
}

TEST_F(Day5Test, PuzzleInputPart2 ) {
    ifstream is( "day5.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "694190cd\n", os.str() );
}
