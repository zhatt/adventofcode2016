#ifndef MD5_H
#define MD5_H

#include <openssl/md5.h>

std::string md5sum( const std::string& input ) {

    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5( (unsigned char*) input.c_str(), input.size(), (unsigned char*)&digest);

    char mdString[33];
    mdString[32] = '\0';

    for( int i = 0; i < 16; i++ ) {
        sprintf( &mdString[i*2], "%02x", (unsigned int)digest[i] );
    }

    return mdString;
}

#endif // MD5_H
