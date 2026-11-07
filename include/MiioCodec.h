#pragma once
#include <cstddef>
#include <cstdint>

// Codec has no Arduino, network or display dependency. Buffers are caller-owned.
class MiioCodec {
 public:
  static constexpr size_t HeaderSize = 32;
  static bool parseToken(const char* hex, uint8_t token[16]);
  void begin(const uint8_t token[16]);
  static void hello(uint8_t packet[32]);
  static bool readHello(const uint8_t* packet, size_t size, uint32_t& deviceId, uint32_t& stamp);
  size_t encode(uint8_t* packet, size_t capacity, const char* json,
                uint32_t deviceId, uint32_t stamp) const;
  // Validates checksum BEFORE decrypting; returns payload length or 0 on failure.
  size_t decode(uint8_t* packet, size_t size, uint32_t deviceId) const;
 private:
  uint8_t token_[16] = {}, key_[16] = {}, iv_[16] = {};
  void checksum(const uint8_t* packet, size_t size, uint8_t digest[16]) const;
};
