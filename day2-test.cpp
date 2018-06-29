
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>

#include "main.h"

using namespace std;

class Day2Test : public ::testing::Test{};

TEST_F( Day2Test, Part1_1 ) {
    istringstream is( "ULL\nRRDD\nLURDL\nUUUUD\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "1985\n", os.str() );
}

TEST_F(Day2Test, PuzzleInputPart1 ) {
    ifstream is( "day2.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "78293\n", os.str() );
}

TEST_F( Day2Test, Part2_1 ) {
    istringstream is( "ULL\nRRDD\nLURDL\nUUUUD\n" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "5DB3\n", os.str() );
}

TEST_F(Day2Test, PuzzleInputPart2 ) {
    ifstream is( "day2.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "AC8C8\n", os.str() );
}
