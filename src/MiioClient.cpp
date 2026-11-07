#include "MiioClient.h"
#include "Lx7Protocol.h"
#include <Arduino.h>

bool MiioClient::begin(const char* ip, const char* hex, const Settings& settings, uint32_t now) {
  reset();
  uint8_t token[16];
  if (!ip_.fromString(ip) || !MiioCodec::parseToken(hex, token)) return false;
  codec_.begin(token);
  settings_ = settings;
  ready_ = udp_.begin(49152) != 0;
  pollAt_ = now - settings_.pollIntervalMs;
  return ready_;
}
void MiioClient::reset() {
  udp_.stop();
  ready_ = session_ = false;
  pending_ = Pending::None;
}
bool MiioClient::sendPacket(size_t size) {
  if (!size || !udp_.beginPacket(ip_, 54321)) return false;
  const auto written = udp_.write(packet_, size);
  const bool sent = udp_.endPacket(); // Release TX buffer even after a partial write.
  return written == size && sent;
}
bool MiioClient::sendQuery(uint32_t now) {
  char json[256];
  if (++requestId_ > 0x7fffffff) requestId_ = 1;
  if (!Lx7Protocol::makeRequest(json, sizeof(json), requestId_)) return false;
  const auto n = codec_.encode(packet_, sizeof(packet_), json, deviceId_, stamp_ + (now - stampAt_) / 1000);
  if (!sendPacket(n)) return false;
  pending_ = Pending::Query;
  sentAt_ = now;
  sawInvalid_ = false;
  return true;
}
MiioClient::Event MiioClient::fail(LinkStatus error) {
  error_ = error;
  pending_ = Pending::None;
  session_ = false; // Re-handshake after timeout, reboot, bad token, RPC or malformed response.
  return Event::Error;
}

MiioClient::Event MiioClient::tick(uint32_t now) {
  if (!ready_) return Event::None;
  // One datagram per loop keeps display/Wi-Fi responsive, even with unrelated UDP traffic.
  const int size = udp_.parsePacket();
  if (size > 0) {
    const bool peer = udp_.remoteIP() == ip_ && udp_.remotePort() == 54321;
    const bool bounded = static_cast<size_t>(size) <= sizeof(packet_);
    int n = 0;
    if (peer && bounded) n = udp_.read(packet_, size);
    // ESP8266 flush() sends TX data; it does not discard RX. parsePacket() discards
    // the previous datagram on the next call, including oversized/foreign packets.
    if (peer && pending_ != Pending::None) {
      if (!bounded || n != size) sawInvalid_ = true;
      else if (pending_ == Pending::Hello) {
        if (MiioCodec::readHello(packet_, size, deviceId_, stamp_)) {
          stampAt_ = now;
          session_ = true;
          if (!sendQuery(now)) return fail(LinkStatus::Timeout);
        } else sawInvalid_ = true;
      } else {
        const auto payloadSize = codec_.decode(packet_, size, deviceId_);
        if (!payloadSize) sawInvalid_ = true;
        else {
          const auto r = Lx7Protocol::parseResponse(reinterpret_cast<char*>(packet_ + 32),
                                                   payloadSize, requestId_, data_);
          if (r == Lx7Protocol::Result::Data) {
            pending_ = Pending::None;
            error_ = LinkStatus::Ok;
            return Event::Sample;
          }
          if (r == Lx7Protocol::Result::RpcError) return fail(LinkStatus::RpcError);
          if (r == Lx7Protocol::Result::Invalid) return fail(LinkStatus::BadData);
          // Late/duplicate response IDs are ignored without accepting stale data.
        }
      }
    }
  }
  if (pending_ != Pending::None) {
    if (elapsed(now, sentAt_, settings_.responseTimeoutMs))
      return fail(sawInvalid_ ? LinkStatus::InvalidPacket : LinkStatus::Timeout);
    return Event::None;
  }
  if (!elapsed(now, pollAt_, settings_.pollIntervalMs)) return Event::None;
  pollAt_ = now;
  // Refresh device timestamp long before millis() wrap can make the session clock ambiguous.
  if (session_ && elapsed(now, stampAt_, 3600000)) session_ = false;
  sawInvalid_ = false;
  if (session_) {
    if (!sendQuery(now)) return fail(LinkStatus::Timeout);
  } else {
    MiioCodec::hello(packet_);
    if (!sendPacket(32)) return fail(LinkStatus::Timeout);
    pending_ = Pending::Hello;
    sentAt_ = now;
  }
  return Event::None;
}
