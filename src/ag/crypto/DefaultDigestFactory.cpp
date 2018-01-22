#include <ag/crypto/DefaultDigestFactory.h>
#include <ag/crypto/SM3Creator.h>

namespace ag {

DigestFactoryPtr DefaultDigestFactory::instance(new DefaultDigestFactory());

DigestFactoryPtr DefaultDigestFactory::getInstance() {
    return instance;
}

DefaultDigestFactory::DefaultDigestFactory() {
    registerDigest(DigestCreatorPtr(new SM3Creator()));
}

DigestCreatorPtr DefaultDigestFactory::registerDigest(DigestCreatorPtr digestCreatorPtr) {
    auto old = digestCreatorMap.find(digestCreatorPtr->getName());
    digestCreatorMap[digestCreatorPtr->getName()] = digestCreatorPtr;
    return old == digestCreatorMap.end() ? DigestCreatorPtr() : old->second;
}

int DefaultDigestFactory::getDigestNameList(std::vector<std::string> & digestNameList) {
    digestNameList.clear();
    for (auto entry : digestCreatorMap)
        digestNameList.emplace_back(entry.first);
    return 0;
}

DigestPtr DefaultDigestFactory::createDigest(const std::string & digestName) {
    auto digestCreator = digestCreatorMap.find(digestName);
    if (digestCreator == digestCreatorMap.end()) {
        return DigestPtr();
    }
    return digestCreator->second->create();
}

}
