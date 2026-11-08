#include "ConfigJson.h"
#include "MiioCodec.h"
#include <ArduinoJson.h>
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

bool validIPv4(const char* s) {
  unsigned octets[4] = {};
  for (size_t i = 0; i < 4; ++i) {
    size_t digits = 0;
    while (*s >= '0' && *s <= '9') {
      if (++digits > 3 || (octets[i] = octets[i] * 10 + (*s++ - '0')) > 255) return false;
    }
    if (!digits || (i < 3 ? *s++ != '.' : *s != 0)) return false;
  }
  return octets[0] != 0 && octets[0] < 224 && octets[3] != 255;
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

bool parseConfig(JsonVariantConst doc, Config& out, const char*& error) {
  error = "CONFIG INVALID";
  if (!doc.is<JsonObjectConst>()) return false;
  if (!doc["schema_version"].isNull() &&
      (!doc["schema_version"].is<unsigned>() || doc["schema_version"].as<unsigned>() != 1)) return false;
  Config c;
  if (!readText(doc["wifi_ssid"], c.ssid) ||
      !readText(doc["wifi_password"], c.password, true) ||
      !readText(doc["device_ip"], c.deviceIp) || !readText(doc["token"], c.token)) return false;
  uint8_t token[16];
  if (!validIPv4(c.deviceIp) || !MiioCodec::parseToken(c.token, token)) return false;
  // Example credentials must never silently become a usable configuration.
  if (!strcmp(c.ssid, "YOUR_WIFI_SSID") || !strcmp(c.deviceIp, "192.0.2.1")) return false;
  if (!doc["admin_password"].isNull() &&
      !readText(doc["admin_password"], c.adminPassword, true)) return false;
  auto& s = c.settings;
  if (!readDuration(doc["poll_interval_ms"], s.pollIntervalMs, 500, 60000) ||
      !readDuration(doc["screen_off_delay_ms"], s.screenOffDelayMs, 0, 3600000) ||
      !readDuration(doc["response_timeout_ms"], s.responseTimeoutMs, 100, 10000) ||
      !readDuration(doc["stale_after_ms"], s.staleAfterMs, 1000, 3600000) ||
      s.staleAfterMs < s.pollIntervalMs + 2 * s.responseTimeoutMs) return false;
  if (!doc["filter_display"].isNull() && !doc["filter_display"].is<const char*>()) return false;
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
  if (!doc["activity_source"].isNull() && !doc["activity_source"].is<const char*>()) return false;
  const char* source = doc["activity_source"] | "tds_change";
  if (!strcmp(source, "run_status")) {
    s.activitySource = ActivitySource::RunStatus;
    if (!doc["making_mask"].is<uint32_t>() || !doc["making_value"].is<uint32_t>()) return false;
    s.makingMask = doc["making_mask"].as<uint32_t>();
    s.makingValue = doc["making_value"].as<uint32_t>();
    if (!s.makingMask || (s.makingValue & ~s.makingMask)) return false;
  } else if (!strcmp(source, "flow_change")) s.activitySource = ActivitySource::FlowChange;
  else if (!strcmp(source, "tds_change")) s.activitySource = ActivitySource::TdsChange;
  else if (!strcmp(source, "unverified")) s.activitySource = ActivitySource::Unverified;
  else return false;
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

void configToJson(JsonDocument& doc, const Config& c, bool secrets) {
  doc.clear();
  doc["schema_version"] = 1;
  doc["wifi_ssid"] = c.ssid;
  doc["device_ip"] = c.deviceIp;
  if (secrets) {
    doc["wifi_password"] = c.password;
    doc["token"] = c.token;
    doc["admin_password"] = c.adminPassword;
  }
  const auto& s = c.settings;
  doc["poll_interval_ms"] = s.pollIntervalMs;
  doc["screen_off_delay_ms"] = s.screenOffDelayMs;
  doc["response_timeout_ms"] = s.responseTimeoutMs;
  doc["stale_after_ms"] = s.staleAfterMs;
  doc["filter_display"] = s.filterDisplay == FilterDisplay::Litres ? "litres" : "percent";
  auto litres = doc["litres_per_flow_unit"].to<JsonArray>();
  litres.add(s.litresPerFlowUnit[0]);
  litres.add(s.litresPerFlowUnit[1]);
  doc["activity_source"] = s.activitySource == ActivitySource::RunStatus ? "run_status" :
      s.activitySource == ActivitySource::FlowChange ? "flow_change" :
      s.activitySource == ActivitySource::TdsChange ? "tds_change" : "unverified";
  doc["making_mask"] = s.makingMask;
  doc["making_value"] = s.makingValue;
  doc["diagnostics"] = c.diagnostics;
  doc["oled_address"] = c.oledAddress;
  doc["oled_sda"] = c.sda;
  doc["oled_scl"] = c.scl;
}

bool mergeConfigUpdate(JsonVariantConst update, const Config& current, Config& out, const char*& error) {
  error = "CONFIG INVALID";
  if (!update.is<JsonObjectConst>()) return false;
  JsonDocument doc;
  configToJson(doc, current, true);
  if (!update["settings"].is<JsonObjectConst>()) return false;
  for (JsonPairConst p : update["settings"].as<JsonObjectConst>()) {
    const char* key = p.key().c_str();
    if (!strcmp(key, "schema_version") || !strcmp(key, "wifi_ssid") ||
        !strcmp(key, "device_ip") || !strcmp(key, "wifi_password") ||
        !strcmp(key, "token") || !strcmp(key, "admin_password") || doc[key].isNull()) return false;
    doc[key].set(p.value());
  }
  for (const char* key : {"wifi_ssid", "device_ip"}) {
    if (!update[key].is<const char*>()) return false;
    doc[key].set(update[key]);
  }
  for (const char* key : {"wifi_password", "token", "admin_password"}) {
    if (!update[key].is<const char*>()) return false;
    if (strlen(update[key].as<const char*>())) doc[key].set(update[key]);
  }
  if (!update["open_wifi"].is<bool>()) return false;
  if (update["open_wifi"].as<bool>()) doc["wifi_password"] = "";
  Config candidate;
  if (!parseConfig(doc.as<JsonVariantConst>(), candidate, error)) return false;
  if (!candidate.adminPassword[0]) { error = "SET ADMIN PASSWORD"; return false; }
  out = candidate;
  error = nullptr;
  return true;
}
