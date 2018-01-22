#include <ag/Security.h>

#include "DefaultSecurityFactory.h"

ag::SecurityFactoryPtr AgSecurityFactory() {
    return ag::DefaultSecurityFactory::getInstance();
}
