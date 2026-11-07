#pragma once
#include <cstddef>
#include <cstdint>

namespace MiioCrypto {
void md5(const void* a, size_t aSize, const void* b, size_t bSize,
         const void* c, size_t cSize, uint8_t out[16]);
void encrypt(const uint8_t key[16], const uint8_t iv[16], uint8_t* data, size_t size);
void decrypt(const uint8_t key[16], const uint8_t iv[16], uint8_t* data, size_t size);
}
