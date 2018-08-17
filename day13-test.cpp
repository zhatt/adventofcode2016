
#include <gtest/gtest.h>
#include <fstream>
#include <list>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>

#include "day13.h"
#include "main.h"

using namespace std;

class Day13Test : public ::testing::Test{};

TEST( Day13Test, Coordinate_Constructor ) {
    const Coordinate a;
    const Coordinate b( 23, 63 );
    const Coordinate c( -64, 72363 );

    EXPECT_EQ( 0, a.x() );
    EXPECT_EQ( 0, a.y() );

    EXPECT_EQ( 23, b.x() );
    EXPECT_EQ( 63, b.y() );

    EXPECT_EQ( -64, c.x() );
    EXPECT_EQ( 72363, c.y() );
}

TEST( Day13Test, Coordinate_Add ) {
    const Coordinate a1( 23, 47 );
    const Coordinate a2( -2723, -6447 );

    const Coordinate b1( 10, 23 );
    const Coordinate b2( -64, 72363 );

    Coordinate s1 = a1 + b1;
    Coordinate s2 = a2 + b2;

    Coordinate s3( 476, 88 );
    s3 += a1;

    Coordinate s4( 23, 18 );
    s4 += a2;

    EXPECT_EQ( 23+10, s1.x() );
    EXPECT_EQ( 47+23, s1.y() );

    EXPECT_EQ( -2723-64, s2.x() );
    EXPECT_EQ( -6447+72363, s2.y() );

    EXPECT_EQ( 476+23, s3.x() );
    EXPECT_EQ( 88+47, s3.y() );

    EXPECT_EQ( 23-2723, s4.x() );
    EXPECT_EQ( 18-6447, s4.y() );
}

TEST( Day13Test, Coordinate_IsNeg ) {
    EXPECT_FALSE( Coordinate().isNeg() );
    EXPECT_FALSE( Coordinate( 10, 20 ).isNeg() );

    EXPECT_TRUE( Coordinate( -10, 20 ).isNeg() );
    EXPECT_TRUE( Coordinate( 10, -20 ).isNeg() );
    EXPECT_TRUE( Coordinate( -10, -20 ).isNeg() );
}

// Test is we have implemented everything needed for unordered_set.
TEST( Day13Test, Coordinate_set ) {
    std::unordered_set<Coordinate> s;
    s.insert( Coordinate( 0, 0 ) );
    s.insert( Coordinate( 1, 2 ) );

    EXPECT_TRUE( s.size() == 2 );
    EXPECT_TRUE( s.find( Coordinate( 0, 0 ) ) != s.end() );
    EXPECT_TRUE( s.find( Coordinate( 1, 2 ) ) != s.end() );
    EXPECT_TRUE( s.find( Coordinate( 2, 2 ) ) == s.end() );

    // Need to be able to copy a set.
    std::unordered_set<Coordinate> t( s );
    EXPECT_TRUE( t.size() == 2 );
    EXPECT_TRUE( t.find( Coordinate( 0, 0 ) ) != t.end() );
    EXPECT_TRUE( t.find( Coordinate( 1, 2 ) ) != t.end() );
    EXPECT_TRUE( t.find( Coordinate( 2, 2 ) ) == t.end() );

}

TEST( Day13Test, Coordinate_isOpen ) {

    // Example input for 10.
    //   0123456789
    // 0 .#.####.##
    // 1 ..#..#...#
    // 2 #....##...
    // 3 ###.#.###.
    // 4 .##..#..#.
    // 5 ..##....#.
    // 6 #...##.###

    const long input = 10;
    EXPECT_TRUE(  Coordinate( 0, 0 ).isOpen( input ) );
    EXPECT_FALSE( Coordinate( 1, 0 ).isOpen( input ) );
    EXPECT_TRUE(  Coordinate( 2, 0 ).isOpen( input ) );
    EXPECT_FALSE( Coordinate( 3, 0 ).isOpen( input ) );

    EXPECT_TRUE(  Coordinate( 3, 4 ).isOpen( input ) );
    EXPECT_FALSE( Coordinate( 5, 6 ).isOpen( input ) );
}

TEST( Day13Test, Part1DescriptionTest ) {
    long input = 10;
    Coordinate target( 7, 4 );

    ostringstream os;

    long output = simulate( SimType::TARGET, 0, input, target );

    EXPECT_EQ( 11, output );
}

TEST(Day13Test, PuzzleInputPart1 ) {
    ifstream is( "day13.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "92\n", os.str() );
}

TEST( Day13Test, Part2DescriptionTest ) {
    long input = 10;
    Coordinate target;  // Unused in MAXSTEPS mode.
    long output = simulate( SimType::MAXSTEPS, 5, input, target );

    EXPECT_EQ( 11, output );
}

TEST(Day13Test, PuzzleInputPart2 ) {
    ifstream is( "day13.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "124\n", os.str() );
}
