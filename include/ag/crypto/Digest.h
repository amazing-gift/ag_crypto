#ifndef AG_CRYPTO_DIGEST_H_
#define AG_CRYPTO_DIGEST_H_

#include <memory>
#include <string>

namespace ag {

class Digest {
public:
    virtual ~Digest() {
    }

    virtual const std::string & getName() = 0;
    virtual int getLength() = 0;

    virtual int init() = 0;
    virtual int update(const void * data, int len) = 0;
    virtual int final(void * data) = 0;

};

typedef std::shared_ptr<Digest> DigestPtr;

}

#endif
