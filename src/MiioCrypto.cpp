#include "MiioCrypto.h"
#include <bearssl/bearssl.h>
#include <cstring>

namespace MiioCrypto {
void md5(const void* a, size_t aSize, const void* b, size_t bSize,
         const void* c, size_t cSize, uint8_t out[16]) {
  br_md5_context ctx;
  br_md5_init(&ctx);
  if (aSize) br_md5_update(&ctx, a, aSize);
  if (bSize) br_md5_update(&ctx, b, bSize);
  if (cSize) br_md5_update(&ctx, c, cSize);
  br_md5_out(&ctx, out);
}
void encrypt(const uint8_t key[16], const uint8_t iv[16], uint8_t* data, size_t size) {
  uint8_t localIv[16];
  memcpy(localIv, iv, 16);
  br_aes_small_cbcenc_keys ctx;
  br_aes_small_cbcenc_init(&ctx, key, 16);
  br_aes_small_cbcenc_run(&ctx, localIv, data, size);
}
void decrypt(const uint8_t key[16], const uint8_t iv[16], uint8_t* data, size_t size) {
  uint8_t localIv[16];
  memcpy(localIv, iv, 16);
  br_aes_small_cbcdec_keys ctx;
  br_aes_small_cbcdec_init(&ctx, key, 16);
  br_aes_small_cbcdec_run(&ctx, localIv, data, size);
}
}
