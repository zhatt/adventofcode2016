#ifndef DAY13_H
#define DAY13_H

#include <bitset>
#include <complex>

class Coordinate {

    // Use a complex number to manage the coordinate instead of reimplementing
    // everything I need.
    std::complex<long> _p;

public:
    Coordinate() : _p( 0, 0 ) {}
    Coordinate( long x, long y ) : _p( x, y ) {}

    const Coordinate operator+( const Coordinate& other ) const {
        return Coordinate( *this ) += other;
    }

    Coordinate& operator+=( const Coordinate& other ) {
        _p += other._p;
        return *this;
    }

    bool operator==( const Coordinate& other ) const {
        return this->_p == other._p;
    }

    long x() const { return _p.real(); }
    long y() const { return _p.imag(); }

    bool isNeg() const { return _p.real() < 0 || _p.imag() < 0; }

    bool isOpen( long input ) const {
        const long x = _p.real();
        const long y = _p.imag();
        const long bits = x*x + 3*x + 2*x*y + y + y*y + input;

        std::bitset<64> bs( bits );

        // Even number of bits set is open.
        return ( bs.count() % 2 ) == 0;
    }

};

template<> struct std::hash<Coordinate> {
    typedef Coordinate argument_type;
    typedef size_t result_type;
    result_type operator()(argument_type const& s) const noexcept {
        result_type const h1 ( hash<long>()( s.x() ) );
        result_type const h2 ( hash<long>{}( s.y() ) );
        return h1 ^ (h2 << 1);
    }
};

enum class SimType {
    TARGET,
    MAXSTEPS
};

long simulate( SimType simtype, long maxSteps, long input, Coordinate target );

#endif
