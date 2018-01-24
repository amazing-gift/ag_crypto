#include <ag/Security.h>

#include <ag/security/DefaultSecurityFactory.h>

ag::SecurityFactoryPtr AgSecurityFactory() {
    return ag::DefaultSecurityFactory::getInstance();
}
