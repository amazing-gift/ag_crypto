#ifndef AG_CRYPTO_DEFAULTDIGESTFACTORY_H_
#define AG_CRYPTO_DEFAULTDIGESTFACTORY_H_

#include <ag/crypto/Digest.h>
#include <ag/crypto/DigestCreator.h>
#include <ag/crypto/DigestFactory.h>
#include <map>
#include <string>
#include <vector>

namespace ag {

class DefaultDigestFactory: public DigestFactory {

private:
    static DigestFactoryPtr instance;

    std::map<std::string, DigestCreatorPtr> digestCreatorMap;

    DefaultDigestFactory();

public:
    static DigestFactoryPtr getInstance();
    virtual DigestCreatorPtr registerDigest(DigestCreatorPtr digestCreatorPtr);
    virtual int getDigestNameList(std::vector<std::string> & digestNameList);
    virtual DigestPtr createDigest(const std::string & digestName);

};

}

#endif
