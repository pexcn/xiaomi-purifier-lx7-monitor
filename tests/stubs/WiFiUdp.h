#pragma once
#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <deque>
#include <vector>

class IPAddress {
 public:
  bool fromString(const char* s) {
    unsigned a, b, c, d;
    char tail;
    if (sscanf(s, "%u.%u.%u.%u%c", &a, &b, &c, &d, &tail) != 4 ||
        a > 255 || b > 255 || c > 255 || d > 255) return false;
    bytes = {uint8_t(a), uint8_t(b), uint8_t(c), uint8_t(d)};
    return true;
  }
  bool operator==(const IPAddress& other) const { return bytes == other.bytes; }
 private:
  std::array<uint8_t, 4> bytes{};
};

namespace FakeUdp {
struct Datagram {
  IPAddress ip;
  uint16_t port;
  std::vector<uint8_t> bytes;
};
inline std::deque<Datagram> incoming;
inline std::vector<Datagram> outgoing;
inline void inject(const uint8_t* p, size_t n, const char* ip = "192.0.2.2", uint16_t port = 54321) {
  Datagram d;
  d.ip.fromString(ip);
  d.port = port;
  d.bytes.assign(p, p + n);
  incoming.push_back(d);
}
}

class WiFiUDP {
 public:
  int begin(uint16_t) { return 1; }
  void stop() {}
  int beginPacket(IPAddress ip, uint16_t port) { tx = {ip, port, {}}; return 1; }
  size_t write(const uint8_t* p, size_t n) { tx.bytes.insert(tx.bytes.end(), p, p + n); return n; }
  int endPacket() { FakeUdp::outgoing.push_back(tx); return 1; }
  int parsePacket() {
    if (FakeUdp::incoming.empty()) return 0;
    rx = FakeUdp::incoming.front();
    FakeUdp::incoming.pop_front();
    return rx.bytes.size();
  }
  IPAddress remoteIP() const { return rx.ip; }
  uint16_t remotePort() const { return rx.port; }
  int read(uint8_t* p, size_t n) { memcpy(p, rx.bytes.data(), n); return n; }
 private:
  FakeUdp::Datagram rx{}, tx{};
};
