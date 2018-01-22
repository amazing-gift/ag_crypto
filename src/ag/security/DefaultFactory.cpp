#include "DefaultSecurityFactory.h"
#include "SM3.h"

namespace ag {

SecurityFactoryPtr DefaultSecurityFactory::instance(new DefaultSecurityFactory());

SecurityFactoryPtr DefaultSecurityFactory::getInstance() {
    return instance;
}

DefaultSecurityFactory::DefaultSecurityFactory() {
    digestCreatorMap["SM3"] = [] (void) {return DigestPtr(new SM3());};
}

DigestNameListPtr DefaultSecurityFactory::getDigestNameList() {
    DigestNameListPtr digestNameListPtr(new DigestNameList());
    for (auto entry : digestCreatorMap)
        digestNameListPtr->emplace_back(entry.first);
    return digestNameListPtr;
}

DigestPtr DefaultSecurityFactory::createDigest(const std::string & digestName) {
    return digestCreatorMap.find(digestName) == digestCreatorMap.end() ? DigestPtr() : digestCreatorMap[digestName]();
}

}
