#ifndef CN_SM3_H_
#define CN_SM3_H_

#include <ag/core/Integer.h>
#include <ag/crypto/Digest.h>
#include <cstdint>

namespace ag {

class SM3: public ::ag::Digest {
private:
    static const std::string name;

    uint64_t total;
    uint8_t buffer[64];

    uint32_t v[8];

    static const uint32_t T[64];
    static const uint8_t PAD[64];

    uint32_t SS1, SS2, TT1, TT2;
    uint32_t A, B, C, D, E, F, G, H;
    uint32_t W[68];
    uint32_t W1[64];

    int updateBlock(const void * block);

public:
    virtual const std::string & getName();
    virtual int getLength();

    virtual int init();
    virtual int update(const void * data, int len);
    virtual int final(void * data);

};

}

#endif
