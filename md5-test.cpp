#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "md5.h"


using namespace std;

class Md5Test : public ::testing::Test{};

TEST( Md5Test, Test1 ) {
    EXPECT_EQ( "900150983cd24fb0d6963f7d28e17f72", md5sum( "abc" ) );
    EXPECT_EQ( "202cb962ac59075b964b07152d234b70", md5sum( "123" ) );
    EXPECT_EQ( "d41d8cd98f00b204e9800998ecf8427e", md5sum( "" ) );
}
