#ifndef AG_CORE_INTEGER_H_
#define AG_CORE_INTEGER_H_

#include <cstdint>

namespace ag {

static inline int readUInt32(uint32_t * i, const void * data) {
    const uint8_t *b = (const uint8_t *) data;
    uint32_t v = (b[0] & 0xFF) << 24;
    v |= (b[1] & 0xFF) << 16;
    v |= (b[2] & 0xFF) << 8;
    v |= b[3] & 0xFF;
    *i = v;
    return sizeof(uint32_t);
}

static inline int writeUInt32(uint32_t n, void * data) {
    uint8_t *b = (uint8_t *) data;
    b[0] = (n >> 24) & 0xFF;
    b[1] = (n >> 16) & 0xFF;
    b[2] = (n >> 8) & 0xFF;
    b[3] = n & 0xFF;
    return sizeof(uint32_t);
}

static inline int writeUInt64(uint64_t i, void * data) {
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

static inline uint32_t rotateUInt32(uint32_t i, int n) {
    return ((i & 0xFFFFFFFF) << n) | (i >> (32 - n));
}

}

#endif
