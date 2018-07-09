#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "day8.h"
#include "main.h"

using namespace std;

class Day8Test : public ::testing::Test{};

TEST( Day8Test, Screen_Construct_4x2 ) {
    Screen s( 4, 2 );

    std::ostringstream os;
    s.display( os );

    std::string result (
        "'    '\n"
        "'    '\n"
    );

    EXPECT_EQ( result, os.str() );
}

TEST( Day8Test, Screen_Construct_1x2 ) {
    Screen s( 1, 2 );

    std::ostringstream os;
    s.display( os );

    std::string result (
        "' '\n"
        "' '\n"
    );

    EXPECT_EQ( result, os.str() );
}

TEST( Day8Test, Screen_Construct_2x1 ) {
    Screen s( 2, 1 );

    std::ostringstream os;
    s.display( os );

    std::string result (
        "'  '\n"
    );

    EXPECT_EQ( result, os.str() );
}

TEST( Day8Test, Screen_Rect_4x2 ) {
    Screen s( 10, 5 );

    s.rect( 4, 2 );
    std::ostringstream os1;
    s.display( os1 );

    std::string result1 (
        "'####      '\n"
        "'####      '\n"
        "'          '\n"
        "'          '\n"
        "'          '\n"
    );
    EXPECT_EQ( result1, os1.str() );

    s.rect( 2, 4 );
    std::ostringstream os2;
    s.display( os2 );

    std::string result2 (
        "'####      '\n"
        "'####      '\n"
        "'##        '\n"
        "'##        '\n"
        "'          '\n"
    );
    EXPECT_EQ( result2, os2.str() );
}

TEST( Day8Test, Screen_RotateRow_1x3 ) {
    Screen s( 10, 5 );

    s.rect( 1, 2 );
    s.rotateRow( 1, 3 );

    std::ostringstream os;
    s.display( os );

    std::string result (
        "'#         '\n"
        "'   #      '\n"
        "'          '\n"
        "'          '\n"
        "'          '\n"
    );
    EXPECT_EQ( result, os.str() );
}

TEST( Day8Test, Screen_RotateColumn_1x3 ) {
    Screen s( 10, 5 );

    s.rect( 2, 2 );
    s.rotateColumn( 1, 3 );

    std::ostringstream os;
    s.display( os );

    std::string result (
        "'#         '\n"
        "'#         '\n"
        "'          '\n"
        "' #        '\n"
        "' #        '\n"
    );
    EXPECT_EQ( result, os.str() );
}

TEST( Day8Test, Screen_NumPixelsLit ) {
    Screen s( 10, 5 );

    s.rect( 2, 2 );

    size_t numLit = s.numPixelsLit();

    EXPECT_EQ( 4, numLit );
}

TEST( Day8Test, Part1_1 ) {
    Screen s( 7, 3 );

    s.rect( 3, 2 );
    s.rotateColumn( 1, 1 );
    s.rotateRow( 0, 4 );
    s.rotateColumn( 1, 2 );

    EXPECT_EQ( 6, s.numPixelsLit() );
}

TEST(Day8Test, PuzzleInputPart1 ) {
    ifstream is( "day8.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "106\n", os.str() );
}

TEST(Day8Test, PuzzleInputPart2 ) {
    ifstream is( "day8.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    const std::string expected(
        "' ##  #### #    #### #     ##  #   #####  ##   ### '\n"
        "'#  # #    #    #    #    #  # #   ##    #  # #    '\n"
        "'#    ###  #    ###  #    #  #  # # ###  #    #    '\n"
        "'#    #    #    #    #    #  #   #  #    #     ##  '\n"
        "'#  # #    #    #    #    #  #   #  #    #  #    # '\n"
        "' ##  #    #### #### ####  ##    #  #     ##  ###  '\n"
    );
    EXPECT_EQ( expected, os.str() );
}

