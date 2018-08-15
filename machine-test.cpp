
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "machine.h"

using namespace std;

class MachineTest : public ::testing::Test {
    protected:

    /*
     * Simplified mainfunc similar to day 12 part 1.
     */
    void mainfunc( istream& is, ostream& os ) {

        Program program;
        program.parse( is, os );

        Machine machine( defaultRegisters, program );

        while( ! machine.pastEnd() ) {
            machine.execute();
        }
    }
};

TEST_F( MachineTest, Dmp ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "dmp\n";

    r << "0:pc=0\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, CpyIm ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "cpy 1 a\n";
    is << "cpy 2 b\n";
    is << "cpy 3 p\n";
    is << "dmp\n";

    r << "3:pc=3\n";
    r << "3:a=1\n";
    r << "3:b=2\n";
    r << "3:p=3\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, Set ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "cpy 1 a\n";
    is << "cpy a b\n";
    is << "cpy 2 c\n";
    is << "cpy c d\n";
    is << "cpy c c\n";
    is << "dmp\n";

    r << "0:pc=5\n";
    r << "0:a=1\n";
    r << "0:b=1\n";
    r << "0:c=2\n";
    r << "0:d=2\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, CpyNeg ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "cpy -1 a\n";
    is << "cpy -2 b\n";
    is << "cpy a c\n";
    is << "cpy b d\n";
    is << "dmp\n";

    r << "0:pc=4\n";
    r << "0:a=-1\n";
    r << "0:b=-2\n";
    r << "0:c=-1\n";
    r << "0:d=-2\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, Inc ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "inc a\n";
    is << "inc b\n";
    is << "inc c\n";
    is << "inc c\n";
    is << "inc c\n";
    is << "inc c\n";
    is << "dmp\n";

    r << "0:pc=6\n";
    r << "0:a=1\n";
    r << "0:b=1\n";
    r << "0:c=4\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, Dec ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "dec a\n"; // a = -1
    is << "dec b\n"; // b = -1
    is << "dec d\n"; // d = -1
    is << "dec d\n"; // d = -2
    is << "dec d\n"; // d = -3
    is << "dmp\n";

    r << "0:pc=5\n";
    r << "0:a=-1\n";
    r << "0:b=-1\n";
    r << "0:d=-3\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, Jnz1 ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "cpy 0 a\n";
    is << "jnz 1 2\n";  // taken
    is << "inc a\n";
    is << "jnz 1 2\n";  // taken
    is << "inc a\n";
    is << "dmp\n";

    r << "0:pc=5\n";
    r << "0:a=0\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, Jnz2 ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "cpy 0 a\n";
    is << "jnz 0 2\n";  // taken
    is << "inc a\n";
    is << "jnz 0 2\n";  // taken
    is << "inc a\n";
    is << "dmp\n";

    r << "0:pc=5\n";
    r << "0:a=2\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, Jnz3 ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "cpy 0 a\n";
    is << "inc a\n";
    is << "cpy a b\n";
    is << "dec b\n"; // b -= 10 via dec
    is << "dec b\n";
    is << "dec b\n";
    is << "dec b\n";
    is << "dec b\n";
    is << "dec b\n";
    is << "dec b\n";
    is << "dec b\n";
    is << "dec b\n";
    is << "dec b\n";
    is << "jnz b -12\n"; // taken 10 times
    is << "dmp\n";

    r << "0:pc=14\n";
    r << "0:a=10\n";
    r << "0:b=0\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, Jnz4 ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "cpy 0 a\n";
    is << "cpy 2 b\n";
    is << "jnz 1 b\n";
    is << "inc a\n";
    is << "inc a\n";
    is << "dmp\n";

    r << "0:pc=5\n";
    r << "0:a=1\n";
    r << "0:b=2\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

