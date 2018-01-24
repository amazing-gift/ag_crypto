#ifndef AG_CRYPTO_DEFAULTDIGESTFACTORY_H_
#define AG_CRYPTO_DEFAULTDIGESTFACTORY_H_

#include <ag/security/Digest.h>
#include <ag/security/SecurityFactory.h>

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <functional>

namespace ag {

class DefaultSecurityFactory: public SecurityFactory {

private:
    static SecurityFactoryPtr instance;

    std::map<std::string, std::function<DigestPtr(void)>> digestCreatorMap;

    DefaultSecurityFactory();

public:
    static SecurityFactoryPtr getInstance();

    virtual DigestNameListPtr getDigestNameList();
    virtual DigestPtr createDigest(const std::string & digestName);

};

}

#endif
