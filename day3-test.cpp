
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>

#include "main.h"

using namespace std;

class Day3Test : public ::testing::Test{};

TEST_F( Day3Test, Part1_1 ) {
    istringstream is( "1 2 2\n5 10 25\n2 2 2\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "2\n", os.str() );
}

TEST_F(Day3Test, PuzzleInputPart1 ) {
    ifstream is( "day3.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "862\n", os.str() );
}

TEST_F(Day3Test, PuzzleInputPart2 ) {
    ifstream is( "day3.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "1577\n", os.str() );
}
