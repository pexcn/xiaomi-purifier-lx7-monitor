#include "Lx7Protocol.h"
#include <ArduinoJson.h>
#include <cmath>
#include <cstdio>

namespace {
bool readCount(JsonVariantConst v, uint32_t& out) {
  if (v.is<uint32_t>()) { out = v.as<uint32_t>(); return true; }
  // Some MiIO firmware returns decimal strings. No null/bool/sentinel-to-zero coercion.
  if (!v.is<const char*>()) return false;
  const char* p = v.as<const char*>();
  if (!*p) return false;
  uint32_t n = 0;
  for (; *p; ++p) {
    if (*p < '0' || *p > '9' || n > (UINT32_MAX - (*p - '0')) / 10) return false;
    n = n * 10 + (*p - '0');
  }
  out = n;
  return true;
}
}

size_t Lx7Protocol::makeRequest(char* out, size_t cap, uint32_t id) {
  const int n = snprintf(out, cap,
      "{\"id\":%lu,\"method\":\"get_prop\",\"params\":[\"tds_in\",\"tds_out\",\"temperature\","
      "\"f1_usedflow\",\"f1_totalflow\",\"f2_usedflow\",\"f2_totalflow\",\"run_status\",\"rinse\"]}",
      static_cast<unsigned long>(id));
  return n > 0 && static_cast<size_t>(n) < cap ? static_cast<size_t>(n) : 0;
}

Lx7Protocol::Result Lx7Protocol::parseResponse(char* json, size_t size, uint32_t id, PurifierData& out) {
  JsonDocument doc;
  if (deserializeJson(doc, json, size, DeserializationOption::NestingLimit(4))) return Result::Invalid;
  uint32_t replyId;
  if (!readCount(doc["id"], replyId)) return Result::Invalid;
  if (replyId != id) return Result::Ignore;
  if (!doc["error"].isNull()) return Result::RpcError;
  const auto a = doc["result"].as<JsonArrayConst>();
  if (a.size() != 9) return Result::Invalid;
  PurifierData d;
  d.tdsInValid = readCount(a[0], d.tdsIn);
  d.tdsOutValid = readCount(a[1], d.tdsOut);
  if (a[2].is<float>()) {
    d.temperature = a[2].as<float>();
    d.temperatureValid = std::isfinite(d.temperature);
  }
  for (size_t i = 0; i < 2; ++i) {
    auto& f = d.filters[i];
    f.valid = readCount(a[3 + 2 * i], f.used) && readCount(a[4 + 2 * i], f.total) && f.total > 0;
  }
  d.runStatusValid = readCount(a[7], d.runStatus);
  d.rinseValid = readCount(a[8], d.rinse);
  if (!(d.tdsInValid || d.tdsOutValid || d.temperatureValid || d.filters[0].valid ||
        d.filters[1].valid || d.runStatusValid)) return Result::Invalid;
  out = d;
  return Result::Data;
}
