#include "MiioCodec.h"
#include "MiioCrypto.h"
#include <cstring>

namespace {
uint32_t read32(const uint8_t* p) {
  return uint32_t(p[0]) << 24 | uint32_t(p[1]) << 16 | uint32_t(p[2]) << 8 | p[3];
}
void write32(uint8_t* p, uint32_t n) {
  p[0] = n >> 24; p[1] = n >> 16; p[2] = n >> 8; p[3] = n;
}
bool validHeader(const uint8_t* p, size_t n) {
  return n >= 32 && n <= 65535 && p[0] == 0x21 && p[1] == 0x31 &&
      ((size_t(p[2]) << 8) | p[3]) == n;
}
int nibble(char c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'a' && c <= 'f') return c - 'a' + 10;
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  return -1;
}
}

bool MiioCodec::parseToken(const char* hex, uint8_t token[16]) {
  if (!hex || strlen(hex) != 32) return false;
  for (size_t i = 0; i < 16; ++i) {
    int a = nibble(hex[2 * i]), b = nibble(hex[2 * i + 1]);
    if (a < 0 || b < 0) return false;
    token[i] = (a << 4) | b;
  }
  return true;
}
void MiioCodec::begin(const uint8_t token[16]) {
  memcpy(token_, token, 16);
  MiioCrypto::md5(token_, 16, nullptr, 0, nullptr, 0, key_);
  MiioCrypto::md5(key_, 16, token_, 16, nullptr, 0, iv_);
}
void MiioCodec::hello(uint8_t packet[32]) {
  memset(packet, 0xff, 32);
  packet[0] = 0x21; packet[1] = 0x31; packet[2] = 0; packet[3] = 32;
}
bool MiioCodec::readHello(const uint8_t* p, size_t size, uint32_t& id, uint32_t& stamp) {
  if (size != 32 || !validHeader(p, size)) return false;
  const auto did = read32(p + 8), ts = read32(p + 12);
  if (!did || did == 0xffffffff || ts == 0xffffffff) return false;
  id = did; stamp = ts;
  // A hello is unauthenticated; never treat its checksum field as a learned token.
  return true;
}
void MiioCodec::checksum(const uint8_t* p, size_t size, uint8_t digest[16]) const {
  MiioCrypto::md5(p, 16, token_, 16, p + 32, size - 32, digest);
}
size_t MiioCodec::encode(uint8_t* p, size_t cap, const char* json, uint32_t id, uint32_t stamp) const {
  const size_t textSize = strlen(json) + 1; // MiIO JSON includes a terminating NUL.
  const size_t encryptedSize = (textSize / 16 + 1) * 16;
  const size_t size = 32 + encryptedSize;
  if (size > cap || size > 65535) return 0;
  memset(p, 0, 32);
  p[0] = 0x21; p[1] = 0x31; p[2] = size >> 8; p[3] = size;
  write32(p + 8, id); write32(p + 12, stamp);
  memcpy(p + 32, json, textSize);
  memset(p + 32 + textSize, encryptedSize - textSize, encryptedSize - textSize);
  MiioCrypto::encrypt(key_, iv_, p + 32, encryptedSize);
  checksum(p, size, p + 16);
  return size;
}
size_t MiioCodec::decode(uint8_t* p, size_t size, uint32_t id) const {
  if (!validHeader(p, size) || size < 48 || (size - 32) % 16 || read32(p + 8) != id) return 0;
  uint8_t digest[16], diff = 0;
  checksum(p, size, digest);
  for (size_t i = 0; i < 16; ++i) diff |= digest[i] ^ p[16 + i];
  if (diff) return 0;
  MiioCrypto::decrypt(key_, iv_, p + 32, size - 32);
  const uint8_t pad = p[size - 1];
  if (!pad || pad > 16) return 0;
  for (size_t i = 0; i < pad; ++i) if (p[size - 1 - i] != pad) return 0;
  size_t n = size - 32 - pad;
  while (n && !p[32 + n - 1]) --n;
  p[32 + n] = 0; // At least one padding byte makes this write safe.
  return n;
}
