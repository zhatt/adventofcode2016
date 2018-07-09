
#ifndef DAY8_H
#define DAY8_H

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class Screen {

    size_t width_;
    size_t height_;
    // pixels[row][col]
    std::vector<std::string> pixels_;

public:
    Screen( size_t width, size_t height ) :
        width_( width ), height_( height ) {

        assert( width );
        assert( height );

        pixels_.resize( height );
        for ( auto& v : pixels_ ) {
            v.resize( width, ' ' );
        }
    }

    void display( std::ostream& os ) const {
        for ( auto& v : pixels_ ) {
            os << "'" << v << "'\n";
        }
    }

    void rect( size_t wide, size_t tall ) {
        for ( size_t row = 0; row < tall; row++ ) {
            for ( size_t col = 0; col < wide; col++ ) {
                pixels_[ row ][ col ] = '#';
            }
        }
    }

    void rotateRow( size_t row, size_t amount ) {
        for ( size_t a = 0; a < amount; a++ ) {
            char last = pixels_[ row ].back();
            pixels_[ row ].insert( pixels_[ row ].begin(), last );
            pixels_[ row ].pop_back();
        }
    }

    void rotateColumn( size_t column, size_t amount ) {
        for ( size_t a = 0; a < amount; a++ ) {
            char last = pixels_[ pixels_.size()-1 ][ column ];
            for ( size_t y = pixels_.size()-1; y > 0; y-- ) {
                pixels_[ y ][ column ] = pixels_[ y-1 ][ column ];
            }
            pixels_[ 0 ][ column ] = last;
        }
    }

    size_t numPixelsLit() const {
        size_t count = 0;

        for ( auto& v : pixels_ ) {
            count += std::count( v.begin(), v.end(), '#' );
        }
        return count;
    }
};

#endif
