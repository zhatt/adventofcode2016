
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>

#include "day7.h"
#include "main.h"

using namespace std;

class Day7Test : public ::testing::Test{};

TEST( Day7Test, ParseIPV7_1 ) {
    std::string input( "abc" );

    SegmentList nonHyperNet;
    SegmentList hyperNet;
    parseIPV7( input, nonHyperNet, hyperNet );

    SegmentList nonHyperNetExpected{ { 0, 3 } };
    SegmentList hyperNetExpected{};

    EXPECT_EQ( nonHyperNetExpected, nonHyperNet );
    EXPECT_EQ( hyperNetExpected, hyperNet );
}

TEST( Day7Test, ParseIPV7_2 ) {
    std::string input( "[abc]" );

    SegmentList nonHyperNet;
    SegmentList hyperNet;
    parseIPV7( input, nonHyperNet, hyperNet );

    SegmentList nonHyperNetExpected{};
    SegmentList hyperNetExpected{ { 1, 4 } };

    EXPECT_EQ( nonHyperNetExpected, nonHyperNet );
    EXPECT_EQ( hyperNetExpected, hyperNet );
}

TEST( Day7Test, ParseIPV7_3 ) {
    std::string input( "xyz[abc]" );

    SegmentList nonHyperNet;
    SegmentList hyperNet;
    parseIPV7( input, nonHyperNet, hyperNet );

    SegmentList nonHyperNetExpected{ { 0, 3 } };
    SegmentList hyperNetExpected{ { 4, 7 } };

    EXPECT_EQ( nonHyperNetExpected, nonHyperNet );
    EXPECT_EQ( hyperNetExpected, hyperNet );
}

TEST( Day7Test, ParseIPV7_4 ) {
    std::string input( "xyz[abc]wxis" );

    SegmentList nonHyperNet;
    SegmentList hyperNet;
    parseIPV7( input, nonHyperNet, hyperNet );

    SegmentList nonHyperNetExpected{
        { 0, 3 },
        { 8, 12 }
    };
    SegmentList hyperNetExpected{ { 4, 7 } };

    EXPECT_EQ( nonHyperNetExpected, nonHyperNet );
    EXPECT_EQ( hyperNetExpected, hyperNet );
}

TEST( Day7Test, ParseIPV7_5 ) {
    std::string input( "xyz[abc]wxis[x]" );

    SegmentList nonHyperNet;
    SegmentList hyperNet;
    parseIPV7( input, nonHyperNet, hyperNet );

    SegmentList nonHyperNetExpected{
        { 0, 3 },
        { 8, 12 }
    };
    SegmentList hyperNetExpected{
        { 4, 7 },
        { 13, 14 }
    };

    EXPECT_EQ( nonHyperNetExpected, nonHyperNet );
    EXPECT_EQ( hyperNetExpected, hyperNet );
}

TEST( Day7Test, HasAbba1 ) {

    EXPECT_TRUE( hasAbba( "abba" ) );
    EXPECT_FALSE( hasAbba( "abc" ) );
    EXPECT_FALSE( hasAbba( "abcdefgh" ) );
    EXPECT_FALSE( hasAbba( "xaaaa" ) );
    EXPECT_TRUE( hasAbba( "ioabbaasdf" ) );

}

TEST( Day7Test, GetAbaList1 ) {
    std::string input( "aba" );
    std::list<std::string> result { "aba" };

    std::list<std::string> abalist;
    parseAba( input, abalist );
    EXPECT_EQ( result, abalist );
}

TEST( Day7Test, GetAbaList2 ) {
    std::string input( "aaa" );
    std::list<std::string> result;

    std::list<std::string> abalist;
    parseAba( input, abalist );
    EXPECT_EQ( result, abalist );
}

TEST( Day7Test, GetAbaList3 ) {
    std::string input( "axax" );
    std::list<std::string> result{ "axa", "xax" };

    std::list<std::string> abalist;
    parseAba( input, abalist );
    EXPECT_EQ( result, abalist );
}

TEST( Day7Test, Part1_1 ) {
    istringstream is(
        "abba[mnop]qrst\n"
        "abcd[bddb]xyyx\n"
        "aaaa[qwer]tyui\n"
        "ioxxoj[asdfgh]zxcvbn\n"
        );

    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "2\n", os.str() );
}

TEST(Day7Test, PuzzleInputPart1 ) {
    ifstream is( "day7.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "115\n", os.str() );
}

TEST( Day7Test, Part2_1 ) {
    istringstream is(
        "aba[bab]xyz\n"
        );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "1\n", os.str() );
}

TEST( Day7Test, Part2_2 ) {
    istringstream is(
        "xyx[xyx]xyx\n"
        );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "0\n", os.str() );
}

TEST( Day7Test, Part2_3 ) {
    istringstream is(
        "aaa[kek]eke\n"
        );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "1\n", os.str() );
}

TEST( Day7Test, Part2_4 ) {
    istringstream is(
        "zazbz[bzb]cdb\n"
        );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "1\n", os.str() );
}

TEST( Day7Test, Part2_all ) {
    istringstream is(
        "aba[bab]xyz\n"
        "xyx[xyx]xyx\n"
        "aaa[kek]eke\n"
        "zazbz[bzb]cdb\n"
        );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "3\n", os.str() );
}

TEST(Day7Test, PuzzleInputPart2 ) {
    ifstream is( "day7.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "231\n", os.str() );
}
