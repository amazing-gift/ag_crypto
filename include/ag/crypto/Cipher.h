#ifndef AG_CRYPTO_CIPHER_H_
#define AG_CRYPTO_CIPHER_H_

#include <ag/core/Object.h>

namespace ag {

class Cipher: public Object {
public:
    virtual int getName() = 0;
    virtual int init() = 0;
    virtual int update(const void * indata, int inlen, void *outdata, int *outlen) = 0;
    virtual int final(void *outdata, int * outlen) = 0;

};

}

#endif
