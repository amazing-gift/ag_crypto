#ifndef AG_SECURITY_DIGEST_H_
#define AG_SECURITY_DIGEST_H_

#include <memory>
#include <string>
#include <vector>

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
typedef std::vector<std::string> DigestNameList;
typedef std::shared_ptr<std::vector<std::string>> DigestNameListPtr;

}

#endif
