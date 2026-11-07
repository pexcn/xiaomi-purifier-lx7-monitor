#pragma once
#include "MiioCodec.h"
#include "Model.h"
#include <WiFiUdp.h>

class MiioClient {
 public:
  enum class Event { None, Sample, Error };
  bool begin(const char* ip, const char* token, const Settings& settings, uint32_t now);
  void reset();
  Event tick(uint32_t now);
  const PurifierData& data() const { return data_; }
  LinkStatus error() const { return error_; }
 private:
  enum class Pending { None, Hello, Query };
  bool sendPacket(size_t size);
  bool sendQuery(uint32_t now);
  Event fail(LinkStatus error);
  WiFiUDP udp_;
  IPAddress ip_;
  MiioCodec codec_;
  Settings settings_;
  uint8_t packet_[768] = {};
  PurifierData data_;
  Pending pending_ = Pending::None;
  bool ready_ = false, session_ = false, sawInvalid_ = false;
  uint32_t deviceId_ = 0, stamp_ = 0, stampAt_ = 0;
  uint32_t requestId_ = 0, sentAt_ = 0, pollAt_ = 0;
  LinkStatus error_ = LinkStatus::Connecting;
};
