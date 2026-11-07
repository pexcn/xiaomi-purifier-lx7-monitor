#include "WebManagement.h"
#include "ConfigJson.h"
#include "WebPage.h"
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <Updater.h>
#include <user_interface.h>

namespace {
void randomHex(char* out, size_t bytes) {
  static const char digits[] = "0123456789abcdef";
  for (size_t i = 0; i < bytes; ++i) {
    const auto n = os_random();
    out[2 * i] = digits[(n >> 4) & 15];
    out[2 * i + 1] = digits[n & 15];
  }
  out[2 * bytes] = 0;
}
}

bool WebManagement::setupAccess() {
  // Only clients reaching the AP interface may use physical-access recovery.
  return ap_ && server_.client().localIP() == WiFi.softAPIP();
}
bool WebManagement::allowed() {
  return setupAccess() || sessions_.accept(server_.header("Cookie").c_str(), millis());
}
void WebManagement::responseHeaders() {
  server_.sendHeader("Cache-Control", "no-store");
  server_.sendHeader("X-Frame-Options", "DENY");
  server_.sendHeader("X-Content-Type-Options", "nosniff");
}
bool WebManagement::authorize(bool redirect) {
  responseHeaders();
  if (allowed()) return true;
  if (redirect) {
    server_.sendHeader("Location", "/login");
    server_.send(303, "text/plain", "Login required");
  } else server_.send(401, "text/plain; charset=utf-8", "请重新登录");
  return false;
}
bool WebManagement::validCsrf() { return server_.arg("csrf") == csrf_; }

void WebManagement::login() {
  responseHeaders();
  if (server_.arg("csrf") != loginCsrf_) { server_.send(403, "text/plain; charset=utf-8", "请刷新登录页后重试"); return; }
  const String password = server_.arg("password");
  if (!passwordMatches(password.c_str(), config_.adminPassword)) {
    server_.send(401, "text/plain; charset=utf-8", "密码不正确"); return;
  }
  char token[33];
  randomHex(token, 16);
  sessions_.logout(server_.header("Cookie").c_str());
  sessions_.create(token, millis());
  server_.sendHeader("Set-Cookie", String(SessionAuth::CookieName) + "=" + token + "; Path=/; HttpOnly; SameSite=Strict");
  server_.send(200, "text/plain", "OK");
}

void WebManagement::logout() {
  if (!authorize()) return;
  if (!validCsrf()) { server_.send(403, "text/plain", "Reload the page and try again"); return; }
  sessions_.logout(server_.header("Cookie").c_str());
  server_.sendHeader("Set-Cookie", String(SessionAuth::CookieName) + "=; Path=/; Max-Age=0; HttpOnly; SameSite=Strict");
  server_.send(200, "text/plain", "OK");
}

void WebManagement::begin(bool configured, uint32_t now) {
  configured_ = configured;
  wifiSeenAt_ = now;
  snprintf(hostname_, sizeof(hostname_), "purifier-%06x", ESP.getChipId());
  randomHex(csrf_, 16);
  randomHex(loginCsrf_, 16);
  if (config_.sda != 0 && config_.scl != 0) pinMode(0, INPUT_PULLUP);
  server_.collectHeaders("Cookie");
  server_.on("/", HTTP_GET, [this]() {
    if (authorize(true)) server_.send_P(200, "text/html; charset=utf-8", ManagementPage);
  });
  server_.on("/login", HTTP_GET, [this]() {
    responseHeaders();
    if (allowed()) {
      server_.sendHeader("Location", "/"); server_.send(303, "text/plain", "Already logged in");
    } else server_.send_P(200, "text/html; charset=utf-8", LoginPage);
  });
  server_.on("/api/login", HTTP_GET, [this]() {
    responseHeaders();
    server_.send(200, "application/json", String("{\"csrf\":\"") + loginCsrf_ +
        "\",\"has_admin_password\":" + (config_.adminPassword[0] ? "true}" : "false}"));
  });
  server_.on("/login", HTTP_POST, [this]() { login(); });
  server_.on("/logout", HTTP_POST, [this]() { logout(); });
  server_.on("/api/config", HTTP_GET, [this]() { getConfig(); });
  server_.on("/config", HTTP_POST, [this]() { postConfig(); });
  server_.on("/update", HTTP_POST, [this]() { finishFirmware(); }, [this]() { uploadFirmware(); });
  server_.onNotFound([this]() { server_.send(404, "text/plain", "Not found"); });
  server_.begin();
  if (!configured_ || !config_.adminPassword[0]) openSetup(now);
}

void WebManagement::openSetup(uint32_t now) {
  if (ap_) return;
  char key[13];
  randomHex(key, 6);
  WiFi.mode(configured_ ? WIFI_AP_STA : WIFI_AP);
  const IPAddress address(192, 168, 4, 1);
  if (!WiFi.softAPConfig(address, address, IPAddress(255, 255, 255, 0)) || !WiFi.softAP(hostname_, key)) {
    display_.message("SETUP AP FAILED"); return;
  }
  ap_ = true;
  apAt_ = now;
  recoveryAttempted_ = true;
  display_.setupAccess(hostname_, key, "http://192.168.4.1");
  Serial.printf("Setup AP: %s at http://192.168.4.1 (key on OLED)\n", hostname_);
}

void WebManagement::getConfig() {
  if (!authorize()) return;
  JsonDocument doc, settings;
  configToJson(settings, config_, false);
  settings.remove("schema_version");
  settings.remove("wifi_ssid");
  settings.remove("device_ip");
  doc["settings"].set(settings.as<JsonVariantConst>());
  doc["wifi_ssid"] = config_.ssid;
  doc["device_ip"] = config_.deviceIp;
  doc["has_token"] = config_.token[0] != 0;
  doc["has_admin_password"] = config_.adminPassword[0] != 0;
  doc["setup_access"] = setupAccess();
  doc["storage_ready"] = configStorageReady();
  doc["csrf"] = csrf_;
  String body;
  serializeJson(doc, body);
  server_.send(200, "application/json", body);
}

void WebManagement::postConfig() {
  if (!authorize()) return;
  if (!validCsrf()) { server_.send(403, "text/plain", "Reload the page and try again"); return; }
  const auto& body = server_.arg("plain");
  JsonDocument doc;
  if (body.length() > 4096 || deserializeJson(doc, body, DeserializationOption::NestingLimit(5))) {
    server_.send(400, "text/plain", "Invalid configuration JSON"); return;
  }
  Config candidate;
  const char* error;
  if (!mergeConfigUpdate(doc.as<JsonVariantConst>(), config_, candidate, error)) {
    server_.send(400, "text/plain", error); return;
  }
  if (!saveConfig(candidate, doc["initialize_storage"] | false, error)) {
    server_.send(500, "text/plain", error); return;
  }
  server_.send(200, "text/plain", "Saved. Restarting.");
  scheduleRestart();
}

void WebManagement::uploadFirmware() {
  auto& u = server_.upload();
  if (u.status == UPLOAD_FILE_START) {
    if (!uploading_) {
      uploadFiles_ = 0; uploadEnded_ = false; uploadError_ = nullptr;
    }
    uploading_ = true;
    ++uploadFiles_;
    if (!allowed() || !validCsrf()) { uploadError_ = "Not authorized. Reload page."; return; }
    if (!config_.adminPassword[0]) { uploadError_ = "Save configuration and admin password first"; return; }
    if (uploadFiles_ != 1 || u.name != "firmware" || !u.filename.endsWith(".bin")) {
      uploadError_ = "Upload one application .bin file"; return;
    }
    const uint32_t freeSpace = ESP.getFreeSketchSpace();
    const uint32_t maxSize = freeSpace > 0x1000 ? (freeSpace - 0x1000) & 0xfffff000 : 0;
    if (!maxSize || !Update.begin(maxSize, U_FLASH)) { uploadError_ = "Cannot start OTA"; return; }
    display_.message("OTA UPDATING");
  } else if (u.status == UPLOAD_FILE_WRITE && !uploadError_) {
    if (Update.write(u.buf, u.currentSize) != u.currentSize) uploadError_ = "Firmware write failed";
  } else if (u.status == UPLOAD_FILE_END) {
    uploadEnded_ = true;
    if (!u.totalSize) uploadError_ = "Firmware file is empty";
  } else if (u.status == UPLOAD_FILE_ABORTED) {
    if (Update.isRunning()) Update.end();
    uploading_ = false;
    uploadError_ = "Firmware upload interrupted";
    display_.message("OTA FAILED");
    notice_ = true; noticeAt_ = millis();
  }
  yield();
}

void WebManagement::finishFirmware() {
  if (!authorize(true)) {
    if (Update.isRunning()) Update.end();
    uploading_ = false;
    return;
  }
  bool success = false;
  if (validCsrf() && uploading_ && uploadFiles_ == 1 && uploadEnded_ && !uploadError_)
    success = Update.end(true); // Commit only after the complete, authenticated request.
  if (Update.isRunning()) Update.end();
  uploading_ = false;
  if (!success) {
    server_.send(400, "text/plain", uploadError_ ? uploadError_ : "Firmware validation failed");
    display_.message("OTA FAILED");
    notice_ = true; noticeAt_ = millis();
    return;
  }
  server_.send(200, "text/html; charset=utf-8", "<meta charset='utf-8'><p>升级成功，正在重启。稍后重新打开设备页面。</p>");
  display_.message("OTA COMPLETE");
  scheduleRestart();
}

void WebManagement::scheduleRestart() { restarting_ = true; restartAt_ = millis(); }
bool WebManagement::ownsDisplay(uint32_t now) const {
  return ap_ || uploading_ || restarting_ || (notice_ && !elapsed(now, noticeAt_, 8000));
}

void WebManagement::tick(uint32_t now) {
  server_.handleClient();
  now = millis(); // A streamed upload can take seconds; don't compare against a pre-upload tick.
  if (restarting_ && elapsed(now, restartAt_, 1000)) { ESP.restart(); return; }
  // GPIO0 is the NodeMCU FLASH button. Hold after boot, never while resetting the board.
  if (config_.sda != 0 && config_.scl != 0) {
    if (digitalRead(0) == LOW) {
      if (!buttonHeld_) { buttonHeld_ = true; buttonHandled_ = false; buttonAt_ = now; }
      if (!buttonHandled_ && elapsed(now, buttonAt_, 3000)) { openSetup(now); buttonHandled_ = true; }
    } else buttonHeld_ = false;
  }
  if (configured_ && WiFi.status() != WL_CONNECTED && !recoveryAttempted_ && elapsed(now, wifiSeenAt_, 60000))
    openSetup(now);
  if (ap_ && !uploading_ && elapsed(now, apAt_, 600000)) {
    WiFi.softAPdisconnect(true);
    WiFi.mode(configured_ ? WIFI_STA : WIFI_OFF);
    ap_ = false;
    if (!configured_) display_.message("HOLD FLASH FOR SETUP");
  }
  if (WiFi.status() == WL_CONNECTED) {
    wifiSeenAt_ = now;
    if (!ap_) recoveryAttempted_ = false;
    if (!mdns_) { mdns_ = MDNS.begin(hostname_); if (mdns_) MDNS.addService("http", "tcp", 80); }
    if (!wifiAnnounced_) {
      wifiAnnounced_ = true;
      Serial.printf("Management: http://%s.local / http://%s\n", hostname_, WiFi.localIP().toString().c_str());
      if (!ap_) {
        display_.message(WiFi.localIP().toString().c_str());
        notice_ = true; noticeAt_ = now;
      }
    }
    if (mdns_) MDNS.update();
  } else {
    wifiAnnounced_ = false;
    if (mdns_) { MDNS.end(); mdns_ = false; }
  }
}
