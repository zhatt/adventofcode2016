/*
--- Day 7: Internet Protocol Version 7 ---

While snooping around the local network of EBHQ, you compile a list of IP
addresses (they're IPv7, of course; IPv6 is much too limited). You'd like to
figure out which IPs support TLS (transport-layer snooping).

An IP supports TLS if it has an Autonomous Bridge Bypass Annotation, or ABBA.
An ABBA is any four-character sequence which consists of a pair of two
different characters followed by the reverse of that pair, such as xyyx or
abba. However, the IP also must not have an ABBA within any hypernet sequences,
which are contained by square brackets.

For example:

  - abba[mnop]qrst supports TLS (abba outside square brackets).
  - abcd[bddb]xyyx does not support TLS (bddb is within square brackets, even
    though xyyx is outside square brackets).
  - aaaa[qwer]tyui does not support TLS (aaaa is invalid; the interior
    characters must be different).
  - ioxxoj[asdfgh]zxcvbn supports TLS (oxxo is outside square brackets, even
    though it's within a larger string).

How many IPs in your puzzle input support TLS?

--- Part Two ---

You would also like to know which IPs support SSL (super-secret listening).

An IP supports SSL if it has an Area-Broadcast Accessor, or ABA, anywhere in
the supernet sequences (outside any square bracketed sections), and a
corresponding Byte Allocation Block, or BAB, anywhere in the hypernet
sequences. An ABA is any three-character sequence which consists of the same
character twice with a different character between them, such as xyx or aba. A
corresponding BAB is the same characters but in reversed positions: yxy and
bab, respectively.

For example:

  - aba[bab]xyz supports SSL (aba outside square brackets with corresponding bab
    within square brackets).
  - xyx[xyx]xyx does not support SSL (xyx, but no corresponding yxy).
  - aaa[kek]eke supports SSL (eke in supernet with corresponding kek in
    hypernet; the aaa sequence is not related, because the interior character
    must be different).
  - zazbz[bzb]cdb supports SSL (zaz has no corresponding aza, but zbz has a
    corresponding bzb, even though zaz and zbz overlap).

How many IPs in your puzzle input support SSL?
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

#include "day7.h"
#include "main.h"

void parseIPV7( const std::string& ipv7,
                SegmentList& nonHyperNet,
                SegmentList& hyperNet ) {

    nonHyperNet.clear();
    hyperNet.clear();

    size_t begin = 0;
    while ( begin < ipv7.size() ) {

        size_t end = ipv7.find_first_of( '[', begin );
        if ( end == std::string::npos ) {
            end = ipv7.size();
        }

        if ( begin != end ) {
            nonHyperNet.push_back( { begin, end } );
        }

        if ( end != ipv7.size() ) {
            begin = end + 1;
            size_t end = ipv7.find_first_of( ']', begin );
            assert( end != std::string::npos );

            hyperNet.push_back( { begin, end } );
            begin = end + 1;

        } else {
            begin = end;
        }
    }
}

bool hasAbba( const std::string& input ) {

    if ( input.size() < 4 ) return false;

    for (  size_t index = 0; index <= input.size() - 4; index++ ) {
        std::string abba = input.substr( index, 4 );

        if ( abba[0] == abba[1] ) continue;

        if ( abba[0] == abba[3] && abba[1] == abba[2] ) return true;
    }

    return false;
}

// Add ABA sequences to abaList.
void parseAba( const std::string& input, std::list<std::string>& abaList ) {

    if ( input.size() < 3 );

    for (  size_t index = 0; index <= input.size() - 3; index++ ) {
        std::string aba = input.substr( index, 3 );

        if ( aba[0] == aba[1] ) continue;

        if ( aba[0] == aba[2] ) {
            abaList.push_back( aba );
        }
    }
}

int mainfunc( std::istream& is, std::ostream& os, Part part ) {

    int count = 0;

    std::string input;
    while( is >> input ) {
        SegmentList nonHyperNetSegments;
        SegmentList hyperNetSegments;

        parseIPV7( input, nonHyperNetSegments, hyperNetSegments );

        if ( part == Part::PART1 ) {
            // hypernet sequences can not contain ABBA.
            bool isNotTls = false;  // Double negative.  Assumes is Tls.
            for ( auto p : hyperNetSegments ) {
                std::string h( input, p.first, p.second - p.first );

                if ( hasAbba( h ) ) {
                    isNotTls = true;
                    break;
                }
            }

            if ( isNotTls ) continue;

            bool isTls = false;
            for ( auto p : nonHyperNetSegments ) {
                std::string h( input, p.first, p.second - p.first );

                if ( hasAbba( h ) ) {
                    isTls = true;
                    break;
                }
            }

            if ( isTls ) count++;

        } else {

            std::list<std::string> abaList;
            std::list<std::string> babList;
            for ( auto p : nonHyperNetSegments ) {
                std::string h( input, p.first, p.second - p.first );
                parseAba( h, abaList );
            }
            for ( auto p : hyperNetSegments ) {
                std::string h( input, p.first, p.second - p.first );
                parseAba( h, babList );
            }

            for ( auto aba : abaList ) {
                std::string bab{ aba[1], aba[0], aba[1] };

                auto iter = std::find( babList.begin(), babList.end(), bab );
                if ( iter != babList.end() ) {
                    count ++;  // is SSL
                    break;
                }
            }
        }
    }

    os << count << std::endl;

    return 0;
}
