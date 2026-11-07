#pragma once
#include "Config.h"
#include "Display.h"
#include "SessionAuth.h"
#include <ESP8266WebServer.h>

class WebManagement {
 public:
  WebManagement(Config& config, Display& display) : config_(config), display_(display) {}
  void begin(bool configured, uint32_t now);
  void tick(uint32_t now);
  bool ownsDisplay(uint32_t now) const;
 private:
  bool allowed();
  bool setupAccess();
  bool authorize(bool redirect = false);
  void responseHeaders();
  void login();
  void logout();
  bool validCsrf();
  void openSetup(uint32_t now);
  void getConfig();
  void postConfig();
  void uploadFirmware();
  void finishFirmware();
  void scheduleRestart();
  Config& config_;
  Display& display_;
  ESP8266WebServer server_{80};
  SessionAuth sessions_;
  char hostname_[24] = {}, csrf_[33] = {}, loginCsrf_[33] = {};
  bool configured_ = false, ap_ = false, mdns_ = false, wifiAnnounced_ = false;
  bool buttonHeld_ = false, buttonHandled_ = false, recoveryAttempted_ = false;
  bool uploading_ = false, uploadEnded_ = false;
  unsigned uploadFiles_ = 0;
  const char* uploadError_ = nullptr;
  bool restarting_ = false;
  uint32_t apAt_ = 0, wifiSeenAt_ = 0, buttonAt_ = 0, restartAt_ = 0, noticeAt_ = 0;
  bool notice_ = false;
};
