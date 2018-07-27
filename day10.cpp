/*
--- Day 10: Balance Bots ---

You come upon a factory in which many robots are zooming around handing small
microchips to each other.

Upon closer examination, you notice that each bot only proceeds when it has two
microchips, and once it does, it gives each one to a different bot or puts it
in a marked "output" bin. Sometimes, bots take microchips from "input" bins,
too.

Inspecting one of the microchips, it seems like they each contain a single
number; the bots must use some logic to decide what to do with each chip. You
access the local control computer and download the bots' instructions (your
puzzle input).

Some of the instructions specify that a specific-valued microchip should be
given to a specific bot; the rest of the instructions indicate what a given bot
should do with its lower-value or higher-value chip.

For example, consider the following instructions:

value 5 goes to bot 2
bot 2 gives low to bot 1 and high to bot 0
value 3 goes to bot 1
bot 1 gives low to output 1 and high to bot 0
bot 0 gives low to output 2 and high to output 0
value 2 goes to bot 2

  - Initially, bot 1 starts with a value-3 chip, and bot 2 starts with a value-2
    chip and a value-5 chip.
  - Because bot 2 has two microchips, it gives its lower one (2) to bot 1 and
    its higher one (5) to bot 0.
  - Then, bot 1 has two microchips; it puts the value-2 chip in output 1 and
    gives the value-3 chip to bot 0.
  - Finally, bot 0 has two microchips; it puts the 3 in output 2 and the 5 in
    output 0.

In the end, output bin 0 contains a value-5 microchip, output bin 1 contains a
value-2 microchip, and output bin 2 contains a value-3 microchip. In this
configuration, bot number 2 is responsible for comparing value-5 microchips
with value-2 microchips.

Based on your instructions, what is the number of the bot that is responsible
for comparing value-61 microchips with value-17 microchips?

--- Part Two ---

What do you get if you multiply together the values of one chip in each of
outputs 0, 1, and 2?
*/


#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>
#include <map>
#include <set>

#include "day10.h"
#include "main.h"

struct Bot {
    std::set<unsigned> values;

    enum class OUTPUT_TYPE {
        NONE,
        BOT,
        OUTPUT
    };

    OUTPUT_TYPE outputLowType = OUTPUT_TYPE::NONE;
    OUTPUT_TYPE outputHighType = OUTPUT_TYPE::NONE;
    unsigned outputToLow = -1;
    unsigned outputToHigh = -1;

    void takeValue( unsigned value ) {
        values.insert( value );
        assert( values.size() <= 2 );
    }

    void giveValuesTo( OUTPUT_TYPE lowType, unsigned lowTo,
                       OUTPUT_TYPE highType, unsigned highTo ) {
        assert( outputLowType == OUTPUT_TYPE::NONE );
        assert( outputHighType == OUTPUT_TYPE::NONE );

        outputLowType = lowType;
        outputHighType = highType;
        outputToLow = lowTo;
        outputToHigh = highTo;
    }
};

void SimulateBots( std::istream& is, unsigned lowValue, unsigned highValue,
                   unsigned& valuesBot, unsigned& product012 ) {

    assert( lowValue < highValue );

    std::map<int,Bot> bots;
    std::map<int,int> outputs;

    std::string line;
    while ( getline( is, line ) ) {
        int value, botNumber, toLowBot, toHighBot;

        char to1[ 7 ];  // size of "output\0"
        char to2[ 7 ];  // size of "output\0"

        if ( sscanf( line.c_str(), "value %d goes to bot %d", &value,
                    &botNumber ) == 2 ) {

            auto& bot = bots[ botNumber ];
            bot.takeValue( value );

        } else if ( sscanf( line.c_str(),
                    "bot %d gives low to %6s %d and high to %6s %d", &botNumber,
                    to1, &toLowBot, to2, &toHighBot ) == 5 ) {

            Bot::OUTPUT_TYPE type1 = strcmp( to1, "bot" ) == 0 ?
                Bot::OUTPUT_TYPE::BOT : Bot::OUTPUT_TYPE::OUTPUT;

            Bot::OUTPUT_TYPE type2 = strcmp( to2, "bot" ) == 0 ?
                Bot::OUTPUT_TYPE::BOT : Bot::OUTPUT_TYPE::OUTPUT;

            auto& bot = bots[ botNumber ];
            bot.giveValuesTo( type1, toLowBot, type2, toHighBot );

        } else {
            assert( ! "Can't parse line" );
        }
    }

    // Since the input is not ordered, some of the bots might not have their
    // input values set yet.  Loop until we have propagated values to all bots.
    while( true ) {
        bool done = true;

        for ( auto p : bots ) {
            if ( p.second.values.size() != 2 ) {
                done = false;
            } else {

                if ( p.second.outputLowType == Bot::OUTPUT_TYPE::BOT ) {
                    auto& low = bots[ p.second.outputToLow ];
                    low.takeValue( *p.second.values.cbegin() );
                } else if ( p.second.outputLowType == Bot::OUTPUT_TYPE::OUTPUT ) {
                    outputs[ p.second.outputToLow ] = *p.second.values.cbegin();
                } else {
                    assert( 0 );
                }

                if ( p.second.outputHighType == Bot::OUTPUT_TYPE::BOT ) {
                    auto& high = bots[ p.second.outputToHigh ];
                    high.takeValue( *p.second.values.crbegin() );
                } else if ( p.second.outputHighType == Bot::OUTPUT_TYPE::OUTPUT ) {
                    outputs[ p.second.outputToHigh ] = *p.second.values.crbegin();
                } else {
                    assert( 0 );
                }
            }
        }

        if ( done ) break;
    }

    // Find the output for part 1.
    for( auto p : bots ) {
        if ( *p.second.values.cbegin() == lowValue &&
             *p.second.values.crbegin() == highValue ) {
            valuesBot = p.first;
        }
    }

    // Calulate the output for part 2.
    product012 = outputs[0] * outputs[1] * outputs[2];
}

int mainfunc( std::istream& is, std::ostream& os, Part part ) {
    unsigned valuesBot;
    unsigned product012;

    SimulateBots( is, 17U, 61U, valuesBot, product012 );
    if ( part == Part::PART1 ) {
        os << valuesBot << std::endl;
    } else {
        os << product012 << std::endl;
    }

    return 0;
}
