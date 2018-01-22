#include "Common.h"
#include "SM3.h"

namespace ag {

const std::string SM3::name = "SM3";

const uint8_t SM3::PAD[64] = { 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

const uint32_t SM3::T[64] = { 0x79CC4519, 0x79CC4519, 0x79CC4519, 0x79CC4519, 0x79CC4519, 0x79CC4519, 0x79CC4519, 0x79CC4519, 0x79CC4519, 0x79CC4519, 0x79CC4519, 0x79CC4519, 0x79CC4519, 0x79CC4519, 0x79CC4519, 0x79CC4519, 0x7A879D8A, 0x7A879D8A,
        0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A,
        0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A,
        0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A, 0x7A879D8A };

static inline uint32_t FF0(uint32_t x, uint32_t y, uint32_t z) {
    return x ^ y ^ z;
}

static inline uint32_t FF16(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) | (x & z) | (y & z);
}

static inline uint32_t GG0(uint32_t x, uint32_t y, uint32_t z) {
    return x ^ y ^ z;
}

static inline uint32_t GG16(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) | ((~x) & z);
}

static inline uint32_t P0(uint32_t x) {
    return x ^ rotateUInt32(x, 9) ^ rotateUInt32(x, 17);
}

static inline uint32_t P1(uint32_t x) {
    return x ^ rotateUInt32(x, 15) ^ rotateUInt32(x, 23);
}

inline int SM3::updateBlock(const void * block) {

    const uint8_t * data = (const uint8_t *) block;

    register int j;

    for (j = 0; j < 16; ++j) {
        readUInt32(&W[j], data + j * 4);
    }

    for (j = 16; j < 68; j++) {
        W[j] = P1(W[j - 16] ^ W[j - 9] ^ rotateUInt32(W[j - 3], 15)) ^ rotateUInt32(W[j - 13], 7) ^ W[j - 6];
    }

    for (j = 0; j < 64; j++) {
        W1[j] = W[j] ^ W[j + 4];
    }

    A = v[0];
    B = v[1];
    C = v[2];
    D = v[3];
    E = v[4];
    F = v[5];
    G = v[6];
    H = v[7];

    for (j = 0; j < 16; j++) {
        SS1 = rotateUInt32((rotateUInt32(A, 12) + E + rotateUInt32(T[j], j)), 7);
        SS2 = SS1 ^ rotateUInt32(A, 12);
        TT1 = FF0(A, B, C) + D + SS2 + W1[j];
        TT2 = GG0(E, F, G) + H + SS1 + W[j];
        D = C;
        C = rotateUInt32(B, 9);
        B = A;
        A = TT1;
        H = G;
        G = rotateUInt32(F, 19);
        F = E;
        E = P0(TT2);
    }

    for (j = 16; j < 64; j++) {
        SS1 = rotateUInt32((rotateUInt32(A, 12) + E + rotateUInt32(T[j], j)), 7);
        SS2 = SS1 ^ rotateUInt32(A, 12);
        TT1 = FF16(A, B, C) + D + SS2 + W1[j];
        TT2 = GG16(E, F, G) + H + SS1 + W[j];
        D = C;
        C = rotateUInt32(B, 9);
        B = A;
        A = TT1;
        H = G;
        G = rotateUInt32(F, 19);
        F = E;
        E = P0(TT2);
    }

    v[0] ^= A;
    v[1] ^= B;
    v[2] ^= C;
    v[3] ^= D;
    v[4] ^= E;
    v[5] ^= F;
    v[6] ^= G;
    v[7] ^= H;

    return 0;
}

const std::string & SM3::getName() {
    return name;
}

int SM3::getLength() {
    return 32;
}

int SM3::init() {
    total = 0;
    v[0] = 0x7380166F;
    v[1] = 0x4914B2B9;
    v[2] = 0x172442D7;
    v[3] = 0xDA8A0600;
    v[4] = 0xA96F30BC;
    v[5] = 0x163138AA;
    v[6] = 0xE38DEE4D;
    v[7] = 0xB0FB0E4E;
    return 0;
}

int SM3::update(const void * data, int dataLength) {

    if (dataLength < 1) {
        return 0;
    }

    uint8_t *dataPtr = (uint8_t *) data;
    uint64_t remain = total % 64;
    uint64_t fill = 64 - remain;

    total += dataLength;

    if (remain > 0 && (uint64_t) dataLength >= fill) {
        memcpy(buffer + remain, dataPtr, fill);
        updateBlock(buffer);
        dataPtr += fill;
        dataLength -= fill;
        remain = 0;
    }

    while (dataLength >= 64) {
        updateBlock(dataPtr);
        dataPtr += 64;
        dataLength -= 64;
    }

    if (dataLength > 0) {
        memcpy(buffer + remain, dataPtr, dataLength);
    }

    return 0;
}

int SM3::final(void * data) {

    uint8_t * digestPtr = (uint8_t *) data;
    uint64_t dataLength = total;

    uint64_t padLength = 64 - (dataLength % 64);
    if (padLength < 9) {
        padLength += 64;
    }
    int errorCode = update(PAD, padLength - 8);
    if (errorCode != 0) {
        return errorCode;
    }

    uint8_t dataLengthBinary[8];
    writeUInt64(dataLength * 8, dataLengthBinary);
    errorCode = update(dataLengthBinary, 8);
    if (errorCode != 0) {
        return errorCode;
    }

    for (int i = 0; i < 8; ++i) {
        writeUInt32(v[i], digestPtr + i * 4);
    }

    return 0;
}

}
