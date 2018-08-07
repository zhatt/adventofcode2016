#include <gtest/gtest.h>
#include <fstream>
#include <list>
#include <iostream>
#include <sstream>
#include <string>

#include "day11.h"
#include "main.h"

using namespace std;

class Day11Test : public ::testing::Test{};

TEST( Day11Test, Floor_Serialize ) {
    Floor floor;
    floor.insert( Item( Item::itemType::CHIP, "promethium" ) );
    floor.insert( Item( Item::itemType::GEN, "promethium" ) );

    std::string s( floor.toString() );

    EXPECT_EQ( "promethium-chip promethium-gen", s );
}

TEST( Day11Test, FloorIsSafe_Empty ) {
    Floor floor;
    EXPECT_EQ( true, floor.isSafe() );
}

TEST( Day11Test, FloorIsSafe_JustChips ) {
    Floor floor;
    floor.insert( { Item::itemType::CHIP, "a" } );
    floor.insert( { Item::itemType::CHIP, "b" } );
    EXPECT_EQ( true, floor.isSafe() );
}

TEST( Day11Test, FloorIsSafe_JustGenerators ) {
    Floor floor;
    floor.insert( { Item::itemType::GEN, "a" } );
    floor.insert( { Item::itemType::GEN, "b" } );
    EXPECT_EQ( true, floor.isSafe() );
}

TEST( Day11Test, FloorIsSafe_ChipUnprotected ) {
    Floor floor;
    floor.insert( { Item::itemType::CHIP, "a" } );
    floor.insert( { Item::itemType::GEN, "b" } );
    EXPECT_EQ( false, floor.isSafe() );
}

TEST( Day11Test, FloorIsSafe_ChipProtected ) {
    Floor floor;
    floor.insert( { Item::itemType::CHIP, "a" } );
    floor.insert( { Item::itemType::GEN, "a" } );
    floor.insert( { Item::itemType::GEN, "b" } );
    EXPECT_EQ( true, floor.isSafe() );
}

TEST( Day11Test, ContainmentFloors_Serialize ) {
    std::istringstream is (
        "a-compatible microchip b generator\n"
        "h-compatible microchip g-compatible microchip\n"
    );

    ContainmentFloors floors( 2 );
    floors.parse( is );

    std::string s( floors.toString() );

    EXPECT_EQ( "2\n0 a-chip b-gen\n1 g-chip h-chip\n", s );
}

TEST( Day11Test, ContainmentFloors_IsSafe_Safe1 ) {
    std::istringstream is (
        "a-compatible microchip b generator a generator\n"
        "h-compatible microchip g-compatible microchip\n"
    );

    ContainmentFloors floors( 2 );
    floors.parse( is );

    EXPECT_EQ( true, floors.isSafe() );
}

TEST( Day11Test, ContainmentFloors_IsSafe_Safe2 ) {
    std::istringstream is (
        "lithium-compatible microchip\n"
        "hydrogen-compatible microchip\n"
        "hydrogen generator lithium generator\n"
    );

    ContainmentFloors floors( 1 );
    floors.parse( is );

    EXPECT_EQ( true, floors.isSafe() );
}

TEST( Day11Test, ContainmentFloors_IsSafe_NotSafe ) {
    std::istringstream is (
        "a-compatible microchip b generator c generator\n"
        "h-compatible microchip g-compatible microchip\n"
    );

    ContainmentFloors floors( 2 );
    floors.parse( is );

    EXPECT_EQ( false, floors.isSafe() );
}

TEST( Day11Test, Perm1 ) {
    Floor floor;
    floor.insert( { Item::itemType::CHIP, "c" } );
    floor.insert( { Item::itemType::CHIP, "b" } );
    floor.insert( { Item::itemType::CHIP, "a" } );
    floor.insert( { Item::itemType::CHIP, "d" } );

    std::set<Floor> elevatorCombos = floor.generateElevatorCombos();
    std::vector<Floor> ecVec( elevatorCombos.begin(), elevatorCombos.end() );

    ASSERT_EQ( 10, ecVec.size() );
    EXPECT_EQ( "a-chip",        ecVec[0].toString() );
    EXPECT_EQ( "a-chip b-chip", ecVec[1].toString() );
    EXPECT_EQ( "a-chip c-chip", ecVec[2].toString() );
    EXPECT_EQ( "a-chip d-chip", ecVec[3].toString() );
    EXPECT_EQ( "b-chip",        ecVec[4].toString() );
    EXPECT_EQ( "b-chip c-chip", ecVec[5].toString() );
    EXPECT_EQ( "b-chip d-chip", ecVec[6].toString() );
    EXPECT_EQ( "c-chip",        ecVec[7].toString() );
    EXPECT_EQ( "c-chip d-chip", ecVec[8].toString() );
    EXPECT_EQ( "d-chip",        ecVec[9].toString() );
}

TEST( Day11Test, Parser1 ) {
    std::istringstream is(
        "The first floor contains a hydrogen-compatible microchip and a lithium-compatible microchip.\n"
        "The second floor contains a hydrogen generator.\n"
        "The third floor contains a lithium generator.\n"
        "The fourth floor contains nothing relevant.\n"
    );

    const std::string output(
        "0\n"
        "0 hydrogen-chip lithium-chip\n"
        "1 hydrogen-gen\n"
        "2 lithium-gen\n"
        "3 \n"
        );

    ContainmentFloors floors( 0 );
    floors.parse( is ) ;

    EXPECT_EQ( output, floors.toString() );
}

TEST( Day11Test, Parser2 ) {
    std::istringstream is1 (
        "The first floor contains a hydrogen-compatible microchip and a lithium-compatible microchip.\n"
        "The second floor contains a hydrogen generator.\n"
        "The third floor contains a lithium generator.\n"
        "The fourth floor contains nothing relevant.\n"
    );

    std::istringstream is2 (
        "\n"
        "The second floor contains a junk generator.\n"
        "The third floor contains a junk-compatible microchip\n"
        "The fourth floor contains nothing relevant.\n"
    );

    const std::string output(
        "0\n"
        "0 hydrogen-chip lithium-chip\n"
        "1 hydrogen-gen junk-gen\n"
        "2 junk-chip lithium-gen\n"
        "3 \n"
        );

    ContainmentFloors floors( 0 );
    floors.parse( is1 ) ;
    floors.parse( is2 ) ;

    EXPECT_EQ( output, floors.toString() );
}

TEST( Day11Test, DescriptionTest ) {
    std::istringstream is(
        "The first floor contains a hydrogen-compatible microchip and a lithium-compatible microchip.\n"
        "The second floor contains a hydrogen generator.\n"
        "The third floor contains a lithium generator.\n"
        "The fourth floor contains nothing relevant.\n"
    );

    ContainmentFloors floors( 0 );
    floors.parse( is );

    Simulate sim;

    unsigned numSteps = sim.simulate( floors ) ;
    EXPECT_EQ( 11, numSteps );
}

TEST(Day11Test, PuzzleInputPart1 ) {
    ifstream is( "day11.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "33\n", os.str() );
}

TEST(Day11Test, PuzzleInputPart2 ) {
    ifstream is( "day11.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "57\n", os.str() );
}
