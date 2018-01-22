#ifndef AG_CRYPTO_DIGESTCREATOR_H_
#define AG_CRYPTO_DIGESTCREATOR_H_

#include <ag/core/Object.h>
#include <ag/crypto/Digest.h>
#include <memory>
#include <string>

namespace ag {

class DigestCreator: public Object {
public:
    virtual const std::string & getName() = 0;
    virtual DigestPtr create() = 0;

};

typedef std::shared_ptr<DigestCreator> DigestCreatorPtr;

}

#endif
