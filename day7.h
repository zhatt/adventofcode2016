#ifndef DAY7_H
#define DAY7_H

#include <list>

typedef std::list<std::pair<size_t,size_t>> SegmentList;
void parseIPV7( const std::string& ipv7,
                SegmentList& nonHyperNet,
                SegmentList& hyperNet );

bool hasAbba( const std::string& input );

void parseAba( const std::string& input, std::list<std::string>& abaList );
#endif
