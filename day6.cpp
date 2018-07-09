/*
--- Day 6: Signals and Noise ---

Something is jamming your communications with Santa. Fortunately, your signal
is only partially jammed, and protocol in situations like this is to switch to
a simple repetition code to get the message through.

In this model, the same message is sent repeatedly. You've recorded the
repeating message signal (your puzzle input), but the data seems quite
corrupted - almost too badly to recover. Almost.

All you need to do is figure out which character is most frequent for each
position. For example, suppose you had recorded the following messages:

eedadn
drvtee
eandsr
raavrd
atevrs
tsrnev
sdttsa
rasrtv
nssdts
ntnada
svetve
tesnvt
vntsnd
vrdear
dvrsen
enarar

The most common character in the first column is e; in the second, a; in the
third, s, and so on. Combining these characters returns the error-corrected
message, easter.

Given the recording in your puzzle input, what is the error-corrected version
of the message being sent?

--- Part Two ---

Of course, that would be the message - if you hadn't agreed to use a modified
repetition code instead.

In this modified code, the sender instead transmits what looks like random
data, but for each character, the character they actually want to send is
slightly less likely than the others. Even after signal-jamming noise, you can
look at the letter distributions in each column and choose the least common
letter to reconstruct the original message.

In the above example, the least common character in the first column is a; in
the second, d, and so on. Repeating this process for the remaining characters
produces the original message, advent.

Given the recording in your puzzle input and this new decoding methodology,
what is the original message that Santa is trying to send?
*/

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "main.h"

class Histogram {
    constexpr static size_t histogramSize = 26;

    size_t charToIndex( char c ) {
        assert( c >= 'a' && c <= 'z' );
        return c = c - 'a';
    }

    // Histogram for each column of characters.  Indexed by [column][character]
    // character array index 0 is 'a'.  See charToIndex().
    std::vector<std::array<int,histogramSize>> data_;

public:

    void addWord( const std::string s ) {

        if ( s.size() > data_.size() ) {
            data_.resize( s.size() );
        }

        // Increment the value in each column.
        for ( size_t index = 0; index < s.size(); index++ ) {
            data_[ index ][ charToIndex( s[index] ) ]++;
        }
    }

    std::string maxResult() const {
        std::string result;

        for ( const auto& col : data_ ) {
            const auto iter = std::max_element( col.begin(), col.end() );
            char c = iter - col.begin() + 'a';
            result += c;
        }

        return result;
    }

    std::string minResult() const {
        std::string result;

        for ( const auto& col : data_ ) {
            size_t minIndex = 0;
            int minCount = std::numeric_limits<int>::max();

            // Find character that was used the least.
            for ( size_t index = 0; index < col.size(); index++ ) {
                // Skip letters that don't exist.
                if ( col[ index ] == 0 ) continue;

                if ( col[ index ] < minCount ) {
                    minCount = col[ index ];
                    minIndex = index;
                }
            }

            char c = minIndex + 'a';
            result += c;
        }

        return result;
    }
};

int mainfunc( std::istream& is, std::ostream& os, Part part ) {

    Histogram histogram;

    std::string input;
    while( is >> input ) {
        histogram.addWord( input );
    }

    if ( part == Part::PART1 ) {
        os << histogram.maxResult() << std::endl;
    } else {
        os << histogram.minResult() << std::endl;
    }

    return 0;
}
