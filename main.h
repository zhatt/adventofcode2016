#ifndef MAIN_H
#define MAIN_H

#include <iosfwd>

enum class Part { PART1, PART2 };

int mainfunc( std::istream&, std::ostream&, Part );

#endif // MAIN_H
