/*
--- Day 3: Squares With Three Sides ---

Now that you can think clearly, you move deeper into the labyrinth of hallways
and office furniture that makes up this part of Easter Bunny HQ. This must be a
graphic design department; the walls are covered in specifications for
triangles.

Or are they?

The design document gives the side lengths of each triangle it describes,
but... 5 10 25? Some of these aren't triangles. You can't help but mark the
impossible ones.

In a valid triangle, the sum of any two sides must be larger than the remaining
side. For example, the "triangle" given above is impossible, because 5 + 10 is
not larger than 25.

In your puzzle input, how many of the listed triangles are possible?

--- Part Two ---

Now that you've helpfully marked up their design documents, it occurs to you
that triangles are specified in groups of three vertically. Each set of three
numbers in a column specifies a triangle. Rows are unrelated.

For example, given the following specification, numbers with the same hundreds
digit would be part of the same triangle:

101 301 501
102 302 502
103 303 503
201 401 601
202 402 602
203 403 603

In your puzzle input, and instead reading by columns, how many of the listed
triangles are possible?
*/

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

#include "main.h"

bool isTriangle( int a, int b, int c ) {
    return ( a + b > c ) && ( a + c > b ) && ( b + c > a );
}

int mainfunc( std::istream& is, std::ostream& os, Part part ) {

    int count = 0;

    std::string line1;
    std::string line2;
    std::string line3;

    while( getline( is, line1 ) &&
           getline( is, line2 ) &&
           getline( is, line3 )) {

        std::istringstream parser1( line1 );
        std::istringstream parser2( line2 );
        std::istringstream parser3( line3 );

        int r1a, r1b, r1c;
        int r2a, r2b, r2c;
        int r3a, r3b, r3c;

        parser1 >> r1a;
        parser1 >> r1b;
        parser1 >> r1c;
        parser2 >> r2a;
        parser2 >> r2b;
        parser2 >> r2c;
        parser3 >> r3a;
        parser3 >> r3b;
        parser3 >> r3c;

        assert( parser1 );
        assert( parser2 );
        assert( parser3 );

        if ( part == Part::PART1 ) {
            if ( isTriangle( r1a, r1b, r1c ) ) count++;
            if ( isTriangle( r2a, r2b, r2c ) ) count++;
            if ( isTriangle( r3a, r3b, r3c ) ) count++;
        } else {
            if ( isTriangle( r1a, r2a, r3a ) ) count++;
            if ( isTriangle( r1b, r2b, r3b ) ) count++;
            if ( isTriangle( r1c, r2c, r3c ) ) count++;
        }
    }

    os << count << std::endl;

    return 0;
}
