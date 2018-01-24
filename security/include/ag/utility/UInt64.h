#ifndef AG_CORE_UINT64_H_
#define AG_CORE_UINT64_H_

#include <cstdint>

namespace ag {

class UInt64 {
public:
    static inline int write(uint64_t i, void * data) {
        uint8_t *b = (uint8_t *) data;
        b[0] = (i >> 56) & 0xFF;
        b[1] = (i >> 48) & 0xFF;
        b[2] = (i >> 40) & 0xFF;
        b[3] = (i >> 32) & 0xFF;
        b[4] = (i >> 24) & 0xFF;
        b[5] = (i >> 16) & 0xFF;
        b[6] = (i >> 8) & 0xFF;
        b[7] = i & 0xFF;
        return sizeof(uint64_t);
    }
};

}

#endif
