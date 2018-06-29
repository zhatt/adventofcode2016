/*
--- Day 4: Security Through Obscurity ---

Finally, you come across an information kiosk with a list of rooms. Of course,
the list is encrypted and full of decoy data, but the instructions to decode
the list are barely hidden nearby. Better remove the decoy data first.

Each room consists of an encrypted name (lowercase letters separated by dashes)
followed by a dash, a sector ID, and a checksum in square brackets.

A room is real (not a decoy) if the checksum is the five most common letters in
the encrypted name, in order, with ties broken by alphabetization. For example:

  - aaaaa-bbb-z-y-x-123[abxyz] is a real room because the most common letters
    are a (5), b (3), and then a tie between x, y, and z, which are listed
    alphabetically.
  - a-b-c-d-e-f-g-h-987[abcde] is a real room because although the letters are
    all tied (1 of each), the first five are listed alphabetically.
  - not-a-real-room-404[oarel] is a real room.
  - totally-real-room-200[decoy] is not.

Of the real rooms from the list above, the sum of their sector IDs is 1514.

What is the sum of the sector IDs of the real rooms?

--- Part Two ---

With all the decoy data out of the way, it's time to decrypt this list and get
moving.

The room names are encrypted by a state-of-the-art shift cipher, which is
nearly unbreakable without the right software. However, the information kiosk
designers at Easter Bunny HQ were not expecting to deal with a master
cryptographer like yourself.

To decrypt a room name, rotate each letter forward through the alphabet a
number of times equal to the room's sector ID. A becomes B, B becomes C, Z
becomes A, and so on. Dashes become spaces.

For example, the real name for qzmt-zixmtkozy-ivhz-343 is very encrypted name.

What is the sector ID of the room where North Pole objects are stored?
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "main.h"

constexpr int checksumSize = 5;

std::string computeChecksum( const std::string& room ) {
    std::vector<int> data( 26, 0 );  // 'a' is index 0

    for ( auto c : room ) {
        if ( c >= 'a' && c <= 'z' ) {
            int index = c - 'a';
            data[ index ]++;
        }
    }

    std::string checksum;

    for ( int i = 0; i < checksumSize; i++ ) {
        auto iter = std::max_element( data.begin(), data.end() );
        int index = iter - data.begin();

        checksum += 'a' + index;
        *iter = 0;
    }

    return checksum;
}

std::string decryptRoom( const std::string& room, int sectorId ) {

    std::string name;

    for ( auto c : room ) {

        if ( c == '-' ) {
            name += ' ';
            continue;
        }

        int d = c - 'a' + sectorId;
        d %= 26;
        d += 'a';

        name += d;
    }

    return name;
}

int mainfunc( std::istream& is, std::ostream& os, Part part ) {

    int sectorIdSum = 0;
    int sectorIdNorthPole = 0;

    std::string record;

    while ( is >> record ) {
        std::size_t posDash = record.find_last_of( '-' );
        assert( posDash != std::string::npos );

        std::size_t posBracket = record.find_last_of( '[' );
        assert( posBracket != std::string::npos );

        std::string room( record, 0, posDash );
        std::string sectorIdStr( record, posDash + 1,
                                 posBracket - posDash - 1 );
        int sectorId = stoi( sectorIdStr );

        std::string checksum( record, posBracket + 1, checksumSize );

        std::string computedChecksum = computeChecksum( room );

        if ( computedChecksum == checksum ) {
            sectorIdSum += sectorId;
        }

        std::string name = decryptRoom( room, sectorId );

        if ( name == "northpole object storage" ) {
            sectorIdNorthPole = sectorId;
        }
    }

    if ( part == Part::PART1 ) {
        os << sectorIdSum << std::endl;
    } else {
        os << sectorIdNorthPole << std::endl;
    }

    return 0;
}

