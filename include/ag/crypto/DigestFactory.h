#ifndef AG_CRYPTO_DIGESTFACTORY_H_
#define AG_CRYPTO_DIGESTFACTORY_H_

#include <ag/core/Object.h>
#include <ag/crypto/DigestCreator.h>
#include <memory>
#include <string>
#include <vector>

namespace ag {

class DigestFactory: public Object {
public:
    virtual DigestCreatorPtr registerDigest(DigestCreatorPtr digestCreatorPtr) = 0;
    virtual int getDigestNameList(std::vector<std::string> & digestNames) = 0;
    virtual DigestPtr createDigest(const std::string & digestName) = 0;

};

typedef std::shared_ptr<DigestFactory> DigestFactoryPtr;

}

#endif
