
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>

#include "main.h"

using namespace std;

class Day6Test : public ::testing::Test{};

TEST_F( Day6Test, Part1_1 ) {
    istringstream is(
        "eedadn\n"
        "drvtee\n"
        "eandsr\n"
        "raavrd\n"
        "atevrs\n"
        "tsrnev\n"
        "sdttsa\n"
        "rasrtv\n"
        "nssdts\n"
        "ntnada\n"
        "svetve\n"
        "tesnvt\n"
        "vntsnd\n"
        "vrdear\n"
        "dvrsen\n"
        "enarar\n"
        );

    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "easter\n", os.str() );
}

TEST_F(Day6Test, PuzzleInputPart1 ) {
    ifstream is( "day6.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "xdkzukcf\n", os.str() );
}

TEST_F( Day6Test, Part2_1 ) {
    istringstream is(
        "eedadn\n"
        "drvtee\n"
        "eandsr\n"
        "raavrd\n"
        "atevrs\n"
        "tsrnev\n"
        "sdttsa\n"
        "rasrtv\n"
        "nssdts\n"
        "ntnada\n"
        "svetve\n"
        "tesnvt\n"
        "vntsnd\n"
        "vrdear\n"
        "dvrsen\n"
        "enarar\n"
        );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "advent\n", os.str() );
}

TEST_F(Day6Test, PuzzleInputPart2 ) {
    ifstream is( "day6.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "cevsgyvd\n", os.str() );
}
