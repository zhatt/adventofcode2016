
/*
--- Day 1: No Time for a Taxicab ---

Santa's sleigh uses a very high-precision clock to guide its movements, and the
clock's oscillator is regulated by stars. Unfortunately, the stars have been
stolen... by the Easter Bunny. To save Christmas, Santa needs you to retrieve
all fifty stars by December 25th.

Collect stars by solving puzzles. Two puzzles will be made available on each
day in the advent calendar; the second puzzle is unlocked when you complete the
first. Each puzzle grants one star. Good luck!

You're airdropped near Easter Bunny Headquarters in a city somewhere. "Near",
unfortunately, is as close as you can get - the instructions on the Easter
Bunny Recruiting Document the Elves intercepted start here, and nobody had time
to work them out further.

The Document indicates that you should start at the given coordinates (where
you just landed) and face North. Then, follow the provided sequence: either
turn left (L) or right (R) 90 degrees, then walk forward the given number of
blocks, ending at a new intersection.

There's no time to follow such ridiculous instructions on foot, though, so you
take a moment and work out the destination. Given that you can only walk on the
street grid of the city, how far is the shortest path to the destination?

For example:

  - Following R2, L3 leaves you 2 blocks East and 3 blocks North, or 5
    blocks away.
  - R2, R2, R2 leaves you 2 blocks due South of your starting position,
    which is 2 blocks away.
  - R5, L5, R5, R3 leaves you 12 blocks away.

How many blocks away is Easter Bunny HQ?

--- Part Two ---

Then, you notice the instructions continue on the back of the Recruiting
Document. Easter Bunny HQ is actually at the first location you visit twice.

For example, if your instructions are R8, R4, R4, R8, the first location you
visit twice is 4 blocks away, due East.

How many blocks away is the first location you visit twice?
*/

#include <algorithm>
#include <cassert>
#include <complex>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>

#include "main.h"

int mainfunc( std::istream& is, std::ostream& os, Part part ) {

    std::string line;
    getline( is, line );
    assert( is );

    replace( line.begin(), line.end(), ',', ' ');

    std::istringstream tokenizer( line );
    std::string command;

    std::complex<int> location( 0, 0 );
    std::complex<int> direction( 0, 1 );  // North
    const std::complex<int> turnLeft( 0, 1 );
    const std::complex<int> turnRight( 0, -1 );

    // Indexed by complex number serialized to string.
    std::unordered_set<std::string> visited;
    bool done = false;

    while ( ( ! done ) && ( tokenizer >> command ) ) {
        std::istringstream parser( command );

        char turnCommand;
        int  distanceCommand;

        parser >> turnCommand;
        parser >> distanceCommand;
        assert( parser );

        if ( command[0] == 'R' ) {
            direction *= turnRight;
        } else if ( command[0] == 'L' ) {
            direction *= turnLeft;

        } else {
            assert( "Bad command direction" );
        }

        // For part one this is equivalent to:
        // location += distanceCommand * direction;
        //
        // for part two we need to make each step separately to check if we have
        // been there before.
        //
        for ( int i = 0; i < distanceCommand; i++ ) {
            // Move one step
            location += 1 * direction;

            std::ostringstream key;
            key << location;

            if ( part == Part::PART2 ) {
                if ( visited.find( key.str()) == visited.end() ) {
                    visited.insert( key.str() );
                } else {
                    // Second visit.
                    done = true;
                    break;
                }
            }
        }
    }

    int howFar = abs( location.real() ) + abs ( location.imag() );
    os << howFar << std::endl;

    return 0;
}

