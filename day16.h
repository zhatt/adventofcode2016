#ifndef DAY16_H
#define DAY16_H

#include <string>
#include <vector>

std::vector<bool> stringToBits( const std::string& startBits );
std::vector<bool> dragonCurve( const std::vector<bool> input );
std::vector<bool> calculateChecksum( std::vector<bool> bits );

// Returns checksum.
std::vector<bool> fillDisk( std::vector<bool> initialState, unsigned size );

#endif
