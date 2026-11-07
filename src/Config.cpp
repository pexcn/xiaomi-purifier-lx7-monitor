#include "Config.h"
#include "MiioCodec.h"
#include <ArduinoJson.h>
#include <LittleFS.h>
#include <IPAddress.h>
#include <cmath>
#include <cstring>

namespace {
template<size_t N>
bool readText(JsonVariantConst value, char (&out)[N], bool allowEmpty = false) {
  if (!value.is<const char*>()) return false;
  const char* s = value.as<const char*>();
  const size_t n = strlen(s);
  if (n >= N || (!allowEmpty && !n)) return false;
  memcpy(out, s, n + 1);
  return true;
}
bool readDuration(JsonVariantConst value, uint32_t& out, uint32_t min, uint32_t max) {
  if (value.isNull()) return true;
  if (!value.is<uint32_t>()) return false;
  const auto n = value.as<uint32_t>();
  if (n < min || n > max) return false;
  out = n;
  return true;
}
}

bool loadConfig(Config& out, const char*& error) {
  error = "CONFIG INVALID";
  if (!LittleFS.begin()) { error = "FS MOUNT FAILED"; return false; }
  auto file = LittleFS.open("/config.json", "r");
  if (!file) { error = "CONFIG MISSING"; return false; }
  if (file.size() > 4096) return false;
  JsonDocument doc;
  if (deserializeJson(doc, file, DeserializationOption::NestingLimit(4))) return false;
  Config c;
  if (!readText(doc["wifi_ssid"], c.ssid) ||
      !readText(doc["wifi_password"], c.password, true) ||
      !readText(doc["device_ip"], c.deviceIp) || !readText(doc["token"], c.token)) return false;
  IPAddress ip;
  uint8_t token[16];
  if (!ip.fromString(c.deviceIp) || ip[0] == 0 || ip[0] >= 224 ||
      ip[3] == 255 || !MiioCodec::parseToken(c.token, token)) return false;
  // Example credentials must never silently become a usable configuration.
  if (!strcmp(c.ssid, "YOUR_WIFI_SSID") || !strcmp(c.deviceIp, "192.0.2.1")) return false;
  auto& s = c.settings;
  if (!readDuration(doc["poll_interval_ms"], s.pollIntervalMs, 500, 60000) ||
      !readDuration(doc["screen_off_delay_ms"], s.screenOffDelayMs, 0, 3600000) ||
      !readDuration(doc["response_timeout_ms"], s.responseTimeoutMs, 100, 10000) ||
      !readDuration(doc["stale_after_ms"], s.staleAfterMs, 1000, 3600000) ||
      s.staleAfterMs < s.pollIntervalMs + 2 * s.responseTimeoutMs) return false;
  const char* mode = doc["filter_display"] | "percent";
  if (!strcmp(mode, "litres")) s.filterDisplay = FilterDisplay::Litres;
  else if (strcmp(mode, "percent")) return false;
  if (!doc["litres_per_flow_unit"].isNull()) {
    const auto a = doc["litres_per_flow_unit"].as<JsonArrayConst>();
    if (a.size() != 2) return false;
    for (size_t i = 0; i < 2; ++i) {
      if (!a[i].is<float>()) return false;
      const float v = a[i].as<float>();
      if (!std::isfinite(v) || v < 0 || v > 1000) return false;
      s.litresPerFlowUnit[i] = v;
    }
  }
  const char* source = doc["activity_source"] | "unverified";
  if (!strcmp(source, "run_status")) {
    s.activitySource = ActivitySource::RunStatus;
    if (!doc["making_mask"].is<uint32_t>() || !doc["making_value"].is<uint32_t>()) return false;
    s.makingMask = doc["making_mask"].as<uint32_t>();
    s.makingValue = doc["making_value"].as<uint32_t>();
    if (!s.makingMask || (s.makingValue & ~s.makingMask)) return false;
  } else if (!strcmp(source, "flow_change")) s.activitySource = ActivitySource::FlowChange;
  else if (strcmp(source, "unverified")) return false;
  if (!doc["diagnostics"].isNull() && !doc["diagnostics"].is<bool>()) return false;
  c.diagnostics = doc["diagnostics"] | false;
  for (const char* key : {"oled_address", "oled_sda", "oled_scl"}) {
    if (!doc[key].isNull() && !doc[key].is<uint8_t>()) return false;
  }
  c.oledAddress = doc["oled_address"] | c.oledAddress;
  c.sda = doc["oled_sda"] | c.sda;
  c.scl = doc["oled_scl"] | c.scl;
  // Restrict I2C to usable GPIOs; avoid flash pins GPIO6..11.
  const auto validPin = [](uint8_t p) { return p <= 5 || (p >= 12 && p <= 16); };
  if ((c.oledAddress != 0x3c && c.oledAddress != 0x3d) || !validPin(c.sda) ||
      !validPin(c.scl) || c.sda == c.scl) return false;
  out = c;
  error = nullptr;
  return true;
}
