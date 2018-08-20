
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "main.h"

using namespace std;

class Day14Test : public ::testing::Test{};

TEST( Day14Test, Part1DescriptionTest ) {
    istringstream is( "abc" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "22728\n", os.str() );
}

TEST(Day14Test, PuzzleInputPart1 ) {
    ifstream is( "day14.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "16106\n", os.str() );
}

TEST( Day14Test, Part2DescriptionTest ) {
    istringstream is( "abc" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "22551\n", os.str() );
}

TEST(Day14Test, PuzzleInputPart2 ) {
    ifstream is( "day14.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "22423\n", os.str() );
}
