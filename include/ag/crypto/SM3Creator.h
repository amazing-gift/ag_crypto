#ifndef AG_CRYPTO_SM3CREATOR_H_
#define AG_CRYPTO_SM3CREATOR_H_

#include <ag/crypto/DigestCreator.h>

namespace ag {

class SM3Creator: public DigestCreator {
private:
    static const std::string name;

public:
    virtual const std::string & getName();
    virtual DigestPtr create();

};

}

#endif
