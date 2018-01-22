#include <ag/crypto/DefaultDigestFactory.h>
#include <ag/crypto/Digest.h>
#include <ag/crypto/DigestFactory.h>
#include <ag/crypto/SM3.h>
#include <cstdint>
#include <cstdio>
#include <memory>

using namespace ag;

int test(DigestFactoryPtr digestFactoryPtr, const std::string & name, void * data, int length) {
    auto digest = digestFactoryPtr->createDigest(name);

    std::vector<uint8_t> result(digest->getLength());

    digest->init();
    digest->update(data, length);
    digest->final(result.data());

    for (int i = 0; i < 32; ++i) {
        if (i && i % 4 == 0)
            printf(" ");
        printf("%02x", result[i]);
    }
    printf("\n");

    return 0;
}

int main() {
    DigestFactoryPtr digestFactoryPtr = DefaultDigestFactory::getInstance();

    uint8_t data1[3] = { 0x61, 0x62, 0x63 };
    test(digestFactoryPtr, "SM3", data1, sizeof(data1));

    uint8_t data2[64] = { 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62,
            0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, };
    test(digestFactoryPtr, "SM3", data2, sizeof(data2));

    return 0;
}
