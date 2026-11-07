#include "ConfigJson.h"
#include <LittleFS.h>

namespace { bool mounted = false; }

bool configStorageReady() { return mounted; }

bool loadConfig(Config& out, const char*& error) {
  // LittleFS defaults to auto-format=true. Disable it explicitly to preserve damaged storage.
  LittleFS.setConfig(LittleFSConfig(false));
  mounted = LittleFS.begin();
  if (!mounted) { error = "FS NEEDS SETUP"; return false; }
  auto file = LittleFS.open("/config.json", "r");
  if (!file) { error = "CONFIG MISSING"; return false; }
  error = "CONFIG INVALID";
  if (file.size() > 4096) return false;
  JsonDocument doc;
  if (deserializeJson(doc, file, DeserializationOption::NestingLimit(4))) return false;
  return parseConfig(doc.as<JsonVariantConst>(), out, error);
}

bool saveConfig(const Config& config, bool initializeStorage, const char*& error) {
  error = "CONFIG SAVE FAILED";
  if (!mounted) {
    if (!initializeStorage) { error = "INITIALIZE STORAGE FIRST"; return false; }
    if (!LittleFS.format() || !(mounted = LittleFS.begin())) return false;
  }
  JsonDocument doc;
  configToJson(doc, config, true);
  auto file = LittleFS.open("/.config.tmp", "w");
  if (!file) return false;
  const size_t expected = measureJson(doc);
  const size_t written = serializeJson(doc, file);
  file.flush();
  file.close();
  if (written != expected || !LittleFS.rename("/.config.tmp", "/config.json")) {
    LittleFS.remove("/.config.tmp");
    return false;
  }
  error = nullptr;
  return true;
}
