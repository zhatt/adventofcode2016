#ifndef DAY15_H
#define DAY15_H

#include <cassert>

class Disc {
    unsigned _size;
    unsigned _start;

    public:

    Disc( unsigned size, unsigned start ) : _size( size ), _start( start ) {
        assert( _size >= 1 );
        assert( _start < size );
    }

    unsigned position( unsigned seconds ) const {
        return ( _start + seconds ) % _size;
    }

    bool open( unsigned seconds ) const {
        return position( seconds ) == 0;
    }
};

#endif // DAY15_H
