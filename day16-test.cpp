
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "day16.h"
#include "main.h"

using namespace std;

class Day16Test : public ::testing::Test{};

TEST( Day16Test, StringToBits ) {
    EXPECT_EQ( std::vector<bool>(), stringToBits( "" ) );
    EXPECT_EQ( std::vector<bool>( { false, true, false } ),
               stringToBits( "010" ) );
}

TEST( Day16Test, DragonCurve ) {
    EXPECT_EQ( stringToBits( "100" ), dragonCurve( stringToBits( "1" ) ) );
    EXPECT_EQ( stringToBits( "001" ), dragonCurve( stringToBits( "0" ) ) );
    EXPECT_EQ( stringToBits( "11111000000" ),
               dragonCurve( stringToBits( "11111" ) ) );
    EXPECT_EQ( stringToBits( "1111000010100101011110000" ),
               dragonCurve( stringToBits( "111100001010" ) ) );
}

TEST( Day16Test, CalculateChecksum ) {
    EXPECT_EQ( stringToBits( "100" ),
               calculateChecksum( stringToBits( "110010110100" ) ) );
}

TEST( Day16Test, Part1DescriptionTest ) {
    auto csum = fillDisk( stringToBits( "10000" ), 20 );

    EXPECT_EQ( stringToBits( "01100" ), csum );
}

TEST(Day16Test, PuzzleInputPart1 ) {
    ifstream is( "day16.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "10111110010110110\n", os.str() );
}

TEST(Day16Test, PuzzleInputPart2 ) {
    ifstream is( "day16.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "01101100001100100\n", os.str() );
}
