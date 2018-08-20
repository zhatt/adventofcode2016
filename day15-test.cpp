
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "day15.h"
#include "main.h"

using namespace std;

class Day15Test : public ::testing::Test{};

TEST( Day15Test, DiscPosition0 ) {
    Disc d1( 5, 0 );

    EXPECT_EQ( 0, d1.position( 0 ) );
    EXPECT_EQ( 1, d1.position( 1 ) );
    EXPECT_EQ( 2, d1.position( 2 ) );
    EXPECT_EQ( 3, d1.position( 3 ) );
    EXPECT_EQ( 4, d1.position( 4 ) );
    EXPECT_EQ( 0, d1.position( 5 ) );
    EXPECT_EQ( 1, d1.position( 6 ) );
}

TEST( Day15Test, DiscPosition1 ) {
    Disc d1( 4, 1 );

    EXPECT_EQ( 1, d1.position( 0 ) );
    EXPECT_EQ( 2, d1.position( 1 ) );
    EXPECT_EQ( 3, d1.position( 2 ) );
    EXPECT_EQ( 0, d1.position( 3 ) );
    EXPECT_EQ( 1, d1.position( 4 ) );
    EXPECT_EQ( 2, d1.position( 5 ) );
    EXPECT_EQ( 3, d1.position( 6 ) );
}

TEST( Day15Test, DiscPosition2 ) {
    Disc d1( 3, 2 );

    EXPECT_EQ( 2, d1.position( 0 ) );
    EXPECT_EQ( 0, d1.position( 1 ) );
    EXPECT_EQ( 1, d1.position( 2 ) );
    EXPECT_EQ( 2, d1.position( 3 ) );
    EXPECT_EQ( 0, d1.position( 4 ) );
    EXPECT_EQ( 1, d1.position( 5 ) );
    EXPECT_EQ( 2, d1.position( 6 ) );
}

TEST( Day15Test, Part1DescriptionTest ) {
    istringstream is(
        "Disc #1 has 5 positions; at time=0, it is at position 4.\n"
        "Disc #2 has 2 positions; at time=0, it is at position 1.\n"
        );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "5\n", os.str() );
}

TEST(Day15Test, PuzzleInputPart1 ) {
    ifstream is( "day15.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "121834\n", os.str() );
}

TEST( Day15Test, Part2DescriptionTest ) {
    istringstream is(
        "Disc #1 has 5 positions; at time=0, it is at position 4.\n"
        "Disc #2 has 2 positions; at time=0, it is at position 1.\n"
        );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "85\n", os.str() );
}

TEST(Day15Test, PuzzleInputPart2 ) {
    ifstream is( "day15.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "3208099\n", os.str() );
}
