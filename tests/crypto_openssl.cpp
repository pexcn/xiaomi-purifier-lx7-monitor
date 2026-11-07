// Host-only backend. The ESP8266 firmware uses the core's BearSSL implementation.
#include "MiioCrypto.h"
#include <openssl/evp.h>
#include <cassert>
#include <vector>
#include <cstring>

namespace MiioCrypto {
void md5(const void* a, size_t na, const void* b, size_t nb,
         const void* c, size_t nc, uint8_t out[16]) {
  auto* ctx = EVP_MD_CTX_new();
  assert(ctx && EVP_DigestInit_ex(ctx, EVP_md5(), nullptr) == 1);
  if (na) assert(EVP_DigestUpdate(ctx, a, na) == 1);
  if (nb) assert(EVP_DigestUpdate(ctx, b, nb) == 1);
  if (nc) assert(EVP_DigestUpdate(ctx, c, nc) == 1);
  unsigned n;
  assert(EVP_DigestFinal_ex(ctx, out, &n) == 1 && n == 16);
  EVP_MD_CTX_free(ctx);
}
void crypt(const uint8_t key[16], const uint8_t iv[16], uint8_t* data, size_t n, bool enc) {
  auto* ctx = EVP_CIPHER_CTX_new();
  assert(ctx && EVP_CipherInit_ex(ctx, EVP_aes_128_cbc(), nullptr, key, iv, enc) == 1);
  assert(EVP_CIPHER_CTX_set_padding(ctx, 0) == 1);
  std::vector<uint8_t> out(n + 16);
  int written, final;
  assert(EVP_CipherUpdate(ctx, out.data(), &written, data, n) == 1);
  assert(EVP_CipherFinal_ex(ctx, out.data() + written, &final) == 1);
  assert(size_t(written + final) == n);
  memcpy(data, out.data(), n);
  EVP_CIPHER_CTX_free(ctx);
}
void encrypt(const uint8_t key[16], const uint8_t iv[16], uint8_t* p, size_t n) { crypt(key, iv, p, n, true); }
void decrypt(const uint8_t key[16], const uint8_t iv[16], uint8_t* p, size_t n) { crypt(key, iv, p, n, false); }
}
