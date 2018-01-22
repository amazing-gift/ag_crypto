#ifndef AG_SECURITY_SECURITYFACTORY_H_
#define AG_SECURITY_SECURITYFACTORY_H_

#include <ag/security/Digest.h>
#include <memory>
#include <string>
#include <vector>

namespace ag {

class SecurityFactory {
public:
    virtual ~SecurityFactory() {
    }

    virtual DigestNameListPtr getDigestNameList() = 0;
    virtual DigestPtr createDigest(const std::string & digestName) = 0;

};

typedef std::shared_ptr<SecurityFactory> SecurityFactoryPtr;

}

#endif
