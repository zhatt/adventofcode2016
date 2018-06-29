
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>

#include "main.h"

using namespace std;

class Day4Test : public ::testing::Test{};

TEST_F( Day4Test, Part1_1 ) {
    istringstream is(
        "aaaaa-bbb-z-y-x-123[abxyz]\n"
        "a-b-c-d-e-f-g-h-987[abcde]\n"
        "not-a-real-room-404[oarel]\n"
        "totally-real-room-200[decoy]\n"
    );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "1514\n", os.str() );
}

TEST_F(Day4Test, PuzzleInputPart1 ) {
    ifstream is( "day4.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "137896\n", os.str() );
}

TEST_F(Day4Test, PuzzleInputPart2 ) {
    ifstream is( "day4.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "501\n", os.str() );
}
