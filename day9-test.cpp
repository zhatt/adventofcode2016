
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "day9.h"
#include "main.h"

using namespace std;

class Day9Test : public ::testing::Test{};

TEST( Day9Test, Part1_1 ) {
    std::string input( "ADVENT" );
    size_t size = DecompressedSize( CompressionType::NON_RECURSIVE, input );
    EXPECT_EQ( 6, size );
}

TEST( Day9Test, Part1_2 ) {
    std::string input( "A(1x5)BC" );
    size_t size = DecompressedSize( CompressionType::NON_RECURSIVE, input );
    EXPECT_EQ( 7, size );
}

TEST( Day9Test, Part1_3 ) {
    std::string input( "(3x3)XYZ" );
    size_t size = DecompressedSize( CompressionType::NON_RECURSIVE, input );
    EXPECT_EQ( 9, size );
}

TEST( Day9Test, Part1_4 ) {
    std::string input( "A(2x2)BCD(2x2)EFG" );
    size_t size = DecompressedSize( CompressionType::NON_RECURSIVE, input );
    EXPECT_EQ( 11, size );
}

TEST( Day9Test, Part1_5 ) {
    std::string input( "(6x1)(1x3)A" );
    size_t size = DecompressedSize( CompressionType::NON_RECURSIVE, input );
    EXPECT_EQ( 6, size );
}

TEST( Day9Test, Part1_6 ) {
    std::string input( "X(8x2)(3x3)ABCY" );
    size_t size = DecompressedSize( CompressionType::NON_RECURSIVE, input );
    EXPECT_EQ( 18, size );
}

TEST(Day9Test, PuzzleInputPart1 ) {
    ifstream is( "day9.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "123908\n", os.str() );
}

TEST( Day9Test, Part2_1 ) {
    std::string input( "(3x3)XYZ" );
    size_t size = DecompressedSize( CompressionType::RECURSIVE, input );
    EXPECT_EQ( 9, size );
}

TEST( Day9Test, Part2_2 ) {
    std::string input( "X(8x2)(3x3)ABCY" );
    size_t size = DecompressedSize( CompressionType::RECURSIVE, input );
    EXPECT_EQ( 20, size );
}

TEST( Day9Test, Part2_3 ) {
    std::string input( "(27x12)(20x12)(13x14)(7x10)(1x12)A" );
    size_t size = DecompressedSize( CompressionType::RECURSIVE, input );
    EXPECT_EQ( 241920, size );
}

TEST( Day9Test, Part2_4 ) {
    std::string input( "(25x3)(3x3)ABC(2x3)XY(5x2)PQRSTX(18x9)(3x2)TWO(5x7)SEVEN" );
    size_t size = DecompressedSize( CompressionType::RECURSIVE, input );

    EXPECT_EQ( 445, size );
}

TEST(Day9Test, PuzzleInputPart2 ) {
    ifstream is( "day9.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "10755693147\n", os.str() );
}
