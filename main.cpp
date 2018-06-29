/*
 * Common main()
 */

#include <cassert>
#include <iostream>

#include "main.h"

using namespace std;

int main( int argc, char* argv[] ) {

    assert( argc == 2 );

    Part part;
    if ( string( argv[1] ) ==  "-1" ) {
        part = Part::PART1;
    } else if ( string( argv[1] ) ==  "-2" ) {
        part = Part::PART2;
    } else {
        assert( ! "Bad part" );
    }

    return mainfunc( cin, cout, part );
}
