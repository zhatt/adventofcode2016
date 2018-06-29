/*
--- Day 2: Bathroom Security ---

You arrive at Easter Bunny Headquarters under cover of darkness. However, you
left in such a rush that you forgot to use the bathroom! Fancy office buildings
like this one usually have keypad locks on their bathrooms, so you search the
front desk for the code.

"In order to improve security," the document you find says, "bathroom codes
will no longer be written down. Instead, please memorize and follow the
procedure below to access the bathrooms."

The document goes on to explain that each button to be pressed can be found by
starting on the previous button and moving to adjacent buttons on the keypad: U
moves up, D moves down, L moves left, and R moves right. Each line of
instructions corresponds to one button, starting at the previous button (or,
for the first line, the "5" button); press whatever button you're on at the end
of each line. If a move doesn't lead to a button, ignore it.

You can't hold it much longer, so you decide to figure out the code as you walk
to the bathroom. You picture a keypad like this:

1 2 3
4 5 6
7 8 9

Suppose your instructions are:

ULL
RRDDD
LURDL
UUUUD

  - You start at "5" and move up (to "2"), left (to "1"), and left (you can't,
    and stay on "1"), so the first button is 1.
  - Starting from the previous button ("1"), you move right twice (to "3") and
    then down three times (stopping at "9" after two moves and ignoring the
    third), ending up with 9.
  - Continuing from "9", you move left, up, right, down, and left, ending with
    8.
  - Finally, you move up four times (stopping at "2"), then down once, ending
    with 5.

So, in this example, the bathroom code is 1985.

Your puzzle input is the instructions from the document you found at the front
desk. What is the bathroom code?


Your puzzle answer was 78293.

The first half of this puzzle is complete! It provides one gold star: *

--- Part Two ---

You finally arrive at the bathroom (it's a several minute walk from the lobby
so visitors can behold the many fancy conference rooms and water coolers on
this floor) and go to punch in the code. Much to your bladder's dismay, the
keypad is not at all like you imagined it. Instead, you are confronted with the
result of hundreds of man-hours of bathroom-keypad-design meetings:

    1
  2 3 4
5 6 7 8 9
  A B C
    D

You still start at "5" and stop when you're at an edge, but given the same
instructions as above, the outcome is very different:

  - You start at "5" and don't move at all (up and left are both edges), ending
    at 5.
  - Continuing from "5", you move right twice and down three times (through "6",
    "7", "B", "D", "D"), ending at D.
  - Then, from "D", you move five more times (through "D", "B", "C", "C", "B"),
    ending at B.
  - Finally, after five more moves, you end at 3.

So, given the actual keypad layout, the code would be 5DB3.

Using the same instructions in your puzzle input, what is the correct bathroom
code?
*/

#include <cassert>
#include <complex>
#include <iostream>
#include <vector>

#include "main.h"

const std::vector<std::vector<char>> keypad1{{
    { 0 ,  0 ,  0 ,  0 , 0 },
    { 0 , '1', '2', '3', 0 },
    { 0 , '4', '5', '6', 0 },
    { 0 , '7', '8', '9', 0 },
    { 0 ,  0 ,  0 ,  0 , 0 },
}};
const std::complex<int> keypad1Start( 2, 2 );

const std::vector<std::vector<char>> keypad2{{
    { 0 ,  0 ,  0 ,  0 ,  0 ,  0,  0 },
    { 0 ,  0 ,  0 , '1',  0 ,  0 , 0 },
    { 0 ,  0 , '2', '3', '4',  0 , 0 },
    { 0 , '5', '6', '7', '8', '9', 0 },
    { 0 ,  0 , 'A', 'B', 'C',  0 , 0 },
    { 0 ,  0 ,  0 , 'D',  0 ,  0 , 0 },
    { 0 ,  0 ,  0 ,  0 ,  0 ,  0,  0 },
}};
const std::complex<int> keypad2Start( 1, 3 );

constexpr std::complex<int> moveU { 0, -1 };
constexpr std::complex<int> moveD { 0, 1 };
constexpr std::complex<int> moveL { -1, 0 };
constexpr std::complex<int> moveR { 1, 0 };

void unlock( std::istream& is, std::ostream& os,
             const std::vector<std::vector<char>>& keypad,
             const std::complex<int> start ) {

    std::complex<int> current( start );

    std::string line;
    while( getline( is, line ) ) {

        for ( char c : line ) {

            std::complex<int> next( current );
            switch ( c ) {
                case 'U': next += moveU; break;
                case 'D': next += moveD; break;
                case 'L': next += moveL; break;
                case 'R': next += moveR; break;
                default:  assert( "invalid input" );
            }

            if ( keypad[next.imag()][next.real()] ) {
                current = next;
           }
        }
        os << keypad[current.imag()][current.real()];
    }

    os << "\n";
}

int mainfunc( std::istream& is, std::ostream& os, Part part ) {
    if ( part == Part::PART1 ) {
        unlock( is, os, keypad1, keypad1Start );
    } else {
        unlock( is, os, keypad2, keypad2Start );
    }

    return 0;
}
