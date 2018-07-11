

#ifndef DAY9_H
#define DAY9_H

#include <string>

enum class CompressionType {
    NON_RECURSIVE,
    RECURSIVE
};

size_t DecompressedSize( CompressionType compType, std::string& s );

#endif // DAY9_H
