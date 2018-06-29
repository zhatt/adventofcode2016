
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>

#include "main.h"

using namespace std;

class Day1Test : public ::testing::Test{};

TEST_F( Day1Test, Part1_1 ) {
    istringstream is( "R2, L3" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "5\n", os.str() );
}

TEST_F( Day1Test, Part1_2 ) {
    istringstream is( "R2, R2, R2" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "2\n", os.str() );
}

TEST_F( Day1Test, Part1_3 ) {
    istringstream is( "R5, L5, R5, R3" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "12\n", os.str() );
}

TEST_F(Day1Test, PuzzleInputPart1 ) {
    ifstream is( "day1.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "236\n", os.str() );
}

TEST_F( Day1Test, Part2_1 ) {
    istringstream is( "R8, R4, R4, R8" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "4\n", os.str() );
}

TEST_F(Day1Test, PuzzleInputPart2 ) {
    ifstream is( "day1.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "182\n", os.str() );
}
