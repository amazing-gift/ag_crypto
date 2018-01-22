#include <ag/crypto/Digest.h>
#include <ag/crypto/SM3.h>
#include <ag/crypto/SM3Creator.h>
#include <memory>

namespace ag {

const std::string SM3Creator::name = "SM3";

const std::string & SM3Creator::getName() {
    return name;
}

DigestPtr SM3Creator::create() {
    return DigestPtr(new SM3());
}

}
