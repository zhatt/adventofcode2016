/*
--- Day 13: A Maze of Twisty Little Cubicles ---

You arrive at the first floor of this new building to discover a much less
welcoming environment than the shiny atrium of the last one. Instead, you are
in a maze of twisty little cubicles, all alike.

Every location in this area is addressed by a pair of non-negative integers
(x,y). Each such coordinate is either a wall or an open space. You can't move
diagonally. The cube maze starts at 0,0 and seems to extend infinitely toward
positive x and y; negative values are invalid, as they represent a location
outside the building. You are in a small waiting area at 1,1.

While it seems chaotic, a nearby morale-boosting poster explains, the layout is
actually quite logical. You can determine whether a given x,y coordinate will
be a wall or an open space using a simple system:

  - Find x*x + 3*x + 2*x*y + y + y*y.
  - Add the office designer's favorite number (your puzzle input).
  - Find the binary representation of that sum; count the number of bits that
    are 1.
      - If the number of bits that are 1 is even, it's an open space.
      - If the number of bits that are 1 is odd, it's a wall.

For example, if the office designer's favorite number were 10, drawing walls as
# and open spaces as ., the corner of the building containing 0,0 would look
like this:

  0123456789
0 .#.####.##
1 ..#..#...#
2 #....##...
3 ###.#.###.
4 .##..#..#.
5 ..##....#.
6 #...##.###

Now, suppose you wanted to reach 7,4. The shortest route you could take is
marked as O:

  0123456789
0 .#.####.##
1 .O#..#...#
2 #OOO.##...
3 ###O#.###.
4 .##OO#OO#.
5 ..##OOO.#.
6 #...##.###

Thus, reaching 7,4 would take a minimum of 11 steps (starting from your current
location, 1,1).

What is the fewest number of steps required for you to reach 31,39?

--- Part Two ---

How many locations (distinct x,y coordinates, including your starting location)
can you reach in at most 50 steps?
*/


#include <bitset>
#include <cassert>
#include <complex>
#include <iostream>
#include <list>
#include <unordered_set>

#include "day13.h"
#include "main.h"

const std::list<Coordinate> nextSteps {
    { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 }
};

struct State {
    long stepCount = 0;
    Coordinate currentLocation;
    std::unordered_set<Coordinate> visited;
};

// Simulate maze traversal with breadth first search of maze.
long simulate( SimType simtype, long maxSteps, long input, Coordinate target ) {
    Coordinate startLocation( 1, 1 );
    assert( !( startLocation == target ) );

    std::unordered_set<Coordinate> visitedInMaxSteps;

    State start;
    start.currentLocation = startLocation;
    start.visited.insert( startLocation );

    std::list<State> queue{ start };

    while( ! queue.empty() ) {

        for ( const auto& inc : nextSteps ) {
            State current = queue.front();

            if ( simtype == SimType::MAXSTEPS ) {
                if ( current.stepCount <= maxSteps ) {
                    // Save to all set.
                    for ( const auto& c : current.visited ) {
                        visitedInMaxSteps.insert( c );
                    }
                }
                if ( current.stepCount == maxSteps ) {
                    continue;
                }

            }

            Coordinate nextLocation = current.currentLocation + inc;

            if ( nextLocation.isNeg() ) continue;
            if ( ! nextLocation.isOpen( input ) ) continue;

            // We can't revisit a square in the simulation.
            if ( current.visited.find( nextLocation ) != current.visited.end()
                 ) {
                continue;
            }

            if ( simtype == SimType::TARGET && nextLocation == target ) {
                // We haven't added this step yet but the start location is
                // in the list so size() is correct value.
                return current.visited.size();
            }

            // Calulate max squares visited.
            current.stepCount ++;
            current.currentLocation = nextLocation;
            current.visited.insert( nextLocation );
            queue.push_back( current );
        }

        queue.pop_front();
    }

    // Shouldn't get here for TARGET mode.  It means bad input or programming
    // error.
    assert( simtype != SimType::TARGET );

    return visitedInMaxSteps.size();

    return 0;
}

int mainfunc( std::istream& is, std::ostream& os, Part part ) {

    long input;
    is >> input;
    assert( input );

    long output;
    if ( part == Part::PART1 ) {
        output = simulate( SimType::TARGET, 0, input, { 31, 39 } );
    } else {
        output = simulate( SimType::MAXSTEPS, 50, input, { 31, 39 } );
    }

    os << output << std::endl;

    return 0;
}

