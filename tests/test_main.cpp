#include "Controller.h"
#include "Lx7Protocol.h"
#include "MiioCodec.h"
#include "MiioCrypto.h"
#include "MiioClient.h"
#include <array>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>

namespace {
Lx7Protocol::Result parse(const char* s, PurifierData& d, uint32_t id = 7) {
  std::string input(s);
  return Lx7Protocol::parseResponse(input.data(), input.size(), id, d);
}
void protocolTests() {
  PurifierData d;
  using Result = Lx7Protocol::Result;
  assert(parse("{\"id\":7,\"result\":[123,5,25,10,7200,20,7200,0,0]}", d) == Result::Data);
  assert(d.tdsIn == 123 && d.tdsOut == 5 && d.runStatusValid && d.rinse == 0);
  assert(d.filters[0].used == 10 && d.filters[1].total == 7200);
  assert(remainingPercent(d.filters[0]) == 99);
  assert(parse("{\"id\":7,\"result\":[\"123\",null,25,\"10\",\"7200\",null,0,\"0\",0]}", d) == Result::Data);
  assert(d.tdsInValid && !d.tdsOutValid && !d.filters[1].valid && d.runStatusValid);
  assert(parse("{\"id\":7,\"result\":[-1,true,25,0,0,9999,100,\"4294967296\",0]}", d) == Result::Data);
  assert(!d.tdsInValid && !d.tdsOutValid && !d.filters[0].valid && !d.runStatusValid);
  assert(remainingPercent(d.filters[1]) == 0);
  assert(parse("{\"id\":7,\"result\":[null,null,null,null,null,null,null,null,null]}", d) == Result::Invalid);
  assert(parse("{\"id\":7,\"result\":[123,5]}", d) == Result::Invalid);
  assert(parse("{\"id\":8,\"result\":[123,5]}", d) == Result::Ignore);
  assert(parse("{\"id\":7,\"error\":{\"code\":-1,\"message\":\"unknown\"}}", d) == Result::RpcError);
  assert(parse("{bad", d) == Result::Invalid);
  assert(remainingPercent({0, 0, true}) == -1);
  assert(remainingPercent({0, UINT32_MAX, true}) == 100);
  assert(remainingPercent({UINT32_MAX - 1, UINT32_MAX, true}) == 0);
  char request[256];
  assert(Lx7Protocol::makeRequest(request, sizeof(request), 7));
  assert(!strstr(request, "usedtime") && strstr(request, "f1_usedflow"));
  assert(!Lx7Protocol::makeRequest(request, 10, 7));
}

void controllerTests() {
  Settings s;
  s.activitySource = ActivitySource::RunStatus;
  // Synthetic rule for tests; this is NOT an lx7 protocol claim.
  s.makingMask = 0x4;
  s.makingValue = 0x4;
  s.staleAfterMs = 60000;
  Controller c(s);
  c.begin(0);
  PurifierData d;
  d.runStatusValid = true;
  d.runStatus = 4;
  c.accept(d, 100);
  assert(c.view(300).awake && c.view(300).activity == Activity::Making);
  d.runStatus = 0;
  c.accept(d, 2100);
  c.accept(d, 4000);
  assert(c.view(32099).awake);
  assert(!c.view(32100).awake); // 30s since observed stop, not since last idle poll.
  c.setLink(LinkStatus::Timeout, 33000);
  assert(!c.view(33000).fresh && c.view(33000).awake);
  c.setLink(LinkStatus::InvalidPacket, 50000);
  assert(!c.view(63000).awake); // Repeated outage errors must not keep waking the screen.
  c.accept(d, 65000);
  assert(c.view(65000).fresh && c.view(65000).awake);
  assert(!c.view(125000).fresh);
  d.runStatusValid = false;
  c.accept(d, 126000);
  assert(c.view(126001).activity == Activity::Unknown && c.view(126001).awake);

  Controller wrap(s);
  const uint32_t start = UINT32_MAX - 1000;
  wrap.begin(start);
  d.runStatusValid = true;
  wrap.accept(d, start);
  assert(wrap.view(start + 29999).awake);
  assert(!wrap.view(start + 30000).awake);

  s.activitySource = ActivitySource::FlowChange;
  Controller flow(s);
  flow.begin(0);
  d.filters[0] = {10, 7200, true};
  flow.accept(d, 0);
  flow.accept(d, 31000);
  assert(!flow.view(31000).awake);
  d.filters[0].used = 20;
  flow.accept(d, 32000);
  assert(flow.view(32000).awake && flow.view(32000).activity == Activity::FlowObserved);
  d.filters[0].used = 0; // A reset/decrease is not production activity.
  flow.accept(d, 61000);
  assert(!flow.view(62000).awake);
  d.filters[0] = {30, 8000, true}; // A changed quota is not flow activity either.
  flow.accept(d, 63000);
  assert(!flow.view(63000).awake);

  s.activitySource = ActivitySource::Unverified;
  Controller unknown(s);
  unknown.begin(0);
  unknown.accept(d, 0);
  unknown.accept(d, 31000);
  assert(unknown.view(31000).awake && unknown.view(31000).activity == Activity::Unknown);
}

void codecTests() {
  const char* tokenHex = "00112233445566778899aabbccddeeff";
  uint8_t token[16];
  assert(MiioCodec::parseToken(tokenHex, token));
  assert(!MiioCodec::parseToken("bad", token));
  assert(!MiioCodec::parseToken("00112233445566778899aabbccddeefg", token));
  assert(MiioCodec::parseToken(tokenHex, token));
  MiioCodec codec;
  codec.begin(token);
  // Independent vector generated with Python hashlib + openssl enc, synthetic credentials/data.
  const char* hex = "2131006000000000000004d26553f1009f867ef263b2e272c2ff06bb0c927db2"
      "55234c3c888e75634a8ae280e9fc469f636f27bb9567d27fdd085328fe4313091"
      "c3e00d27999aafa65ce8c10f464f7af4b985af822fcf13d5144e56893d01b09";
  std::array<uint8_t, 96> expected{};
  for (size_t i = 0; i < expected.size(); ++i) {
    unsigned n;
    assert(sscanf(hex + 2 * i, "%2x", &n) == 1);
    expected[i] = n;
  }
  const char* json = "{\"id\":7,\"result\":[123,5,25,10,7200,20,7200,0,0]}";
  uint8_t packet[256];
  const size_t n = codec.encode(packet, sizeof(packet), json, 1234, 1700000000);
  assert(n == expected.size() && !memcmp(packet, expected.data(), n));
  assert(codec.decode(packet, n, 1234) == strlen(json));
  assert(!strcmp(reinterpret_cast<char*>(packet + 32), json));
  memcpy(packet, expected.data(), n);
  packet[40] ^= 1;
  assert(codec.decode(packet, n, 1234) == 0); // Checksum rejects ciphertext tampering.
  memcpy(packet, expected.data(), n);
  assert(codec.decode(packet, n - 1, 1234) == 0);
  assert(codec.decode(packet, n, 4321) == 0);
  packet[0] = 0;
  assert(codec.decode(packet, n, 1234) == 0);
  assert(codec.encode(packet, 40, json, 1234, 1) == 0);

  uint8_t key[16], iv[16];
  MiioCrypto::md5(token, 16, nullptr, 0, nullptr, 0, key);
  MiioCrypto::md5(key, 16, token, 16, nullptr, 0, iv);
  memcpy(packet, expected.data(), n);
  MiioCrypto::decrypt(key, iv, packet + 32, n - 32);
  packet[n - 1] = 0; // Correctly signed ciphertext containing invalid PKCS#7 padding.
  MiioCrypto::encrypt(key, iv, packet + 32, n - 32);
  MiioCrypto::md5(packet, 16, token, 16, packet + 32, n - 32, packet + 16);
  assert(codec.decode(packet, n, 1234) == 0);

  MiioCodec::hello(packet);
  uint32_t id = 0, ts = 0;
  assert(!MiioCodec::readHello(packet, 32, id, ts)); // Reject an echoed probe.
  packet[8] = 0; packet[9] = 0; packet[10] = 4; packet[11] = 0xd2;
  packet[12] = 0x65; packet[13] = 0x53; packet[14] = 0xf1; packet[15] = 0;
  assert(MiioCodec::readHello(packet, 32, id, ts) && id == 1234 && ts == 1700000000);
  assert(!MiioCodec::readHello(packet, 31, id, ts));
}

void transportTests() {
  using Event = MiioClient::Event;
  FakeUdp::incoming.clear();
  FakeUdp::outgoing.clear();
  Settings settings;
  const char* tokenHex = "00112233445566778899aabbccddeeff";
  uint8_t token[16], packet[1024];
  assert(MiioCodec::parseToken(tokenHex, token));
  MiioCodec codec;
  codec.begin(token);
  MiioClient client;
  assert(client.begin("192.0.2.2", tokenHex, settings, 0));
  assert(client.tick(0) == Event::None);
  assert(FakeUdp::outgoing.size() == 1 && FakeUdp::outgoing.back().bytes.size() == 32);
  // Valid-looking hello from a foreign IP/port must not create a session.
  MiioCodec::hello(packet);
  packet[8] = 0; packet[9] = 0; packet[10] = 4; packet[11] = 0xd2;
  packet[12] = 0x65; packet[13] = 0x53; packet[14] = 0xf1; packet[15] = 0;
  FakeUdp::inject(packet, 32, "192.0.2.3");
  assert(client.tick(1) == Event::None && FakeUdp::outgoing.size() == 1);
  FakeUdp::inject(packet, 32, "192.0.2.2", 12345);
  assert(client.tick(2) == Event::None && FakeUdp::outgoing.size() == 1);
  FakeUdp::inject(packet, 32);
  assert(client.tick(10) == Event::None && FakeUdp::outgoing.size() == 2);
  auto sent = FakeUdp::outgoing.back().bytes;
  assert(codec.decode(sent.data(), sent.size(), 1234));
  assert(strstr(reinterpret_cast<char*>(sent.data() + 32), "\"id\":1"));
  auto n = codec.encode(packet, sizeof(packet),
      "{\"id\":9,\"result\":[123,5,25,10,7200,20,7200,0,0]}", 1234, 1700000000);
  FakeUdp::inject(packet, n);
  assert(client.tick(20) == Event::None); // An old ID must not be accepted.
  n = codec.encode(packet, sizeof(packet),
      "{\"id\":1,\"result\":[123,5,25,10,7200,20,7200,0,0]}", 1234, 1700000000);
  FakeUdp::inject(packet, n);
  assert(client.tick(30) == Event::Sample && client.data().tdsOut == 5);
  assert(FakeUdp::outgoing.size() == 2); // Receiving must not send empty packets.
  assert(client.tick(1999) == Event::None && FakeUdp::outgoing.size() == 2);
  client.tick(2000);
  assert(FakeUdp::outgoing.size() == 3);
  assert(client.tick(3500) == Event::Error && client.error() == LinkStatus::Timeout);
  client.tick(4000);
  assert(FakeUdp::outgoing.back().bytes.size() == 32); // Re-handshake after a timeout.
  FakeUdp::inject(packet, sizeof(packet)); // Oversize input must not overflow the packet buffer.
  assert(client.tick(4100) == Event::None);
  assert(client.tick(5500) == Event::Error && client.error() == LinkStatus::InvalidPacket);
  client.reset();
  assert(client.tick(10000) == Event::None);
}
}

int main() {
  protocolTests();
  controllerTests();
  codecTests();
  transportTests();
  puts("PASS: lx7 parsing, flow lifetime, screen timers, MiIO codec and UDP state machine");
}
