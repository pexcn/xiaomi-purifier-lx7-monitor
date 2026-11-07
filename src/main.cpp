#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "Config.h"
#include "Controller.h"
#include "MiioClient.h"
#include "Ssd1306Display.h"
#include "WebManagement.h"
#include "AppLog.h"

namespace {
Config config;
MiioClient purifier;
Controller* controller = nullptr;
Ssd1306Display oled(config.settings);
Display& display = oled;
WebManagement management(config, display);
bool configured = false, connected = false;
uint32_t lastWifiTry = 0, lastRender = 0;
LinkStatus reported = LinkStatus::Connecting;

void report(LinkStatus status) {
  if (reported == status) return;
  reported = status;
  const char* message = PSTR("Connecting");
  switch (status) {
    case LinkStatus::Ok: message = PSTR("MiIO data received; communication available"); break;
    case LinkStatus::WifiDown: message = PSTR("Wi-Fi disconnected; retrying"); break;
    case LinkStatus::Timeout: message = PSTR("MiIO timeout; retrying handshake/query"); break;
    case LinkStatus::InvalidPacket: message = PSTR("MiIO packet validation failed; retrying"); break;
    case LinkStatus::RpcError: message = PSTR("MiIO RPC error; retrying"); break;
    case LinkStatus::BadData: message = PSTR("MiIO response has invalid data; retrying"); break;
    default: break;
  }
  logEvent_P(status == LinkStatus::Ok || status == LinkStatus::Connecting ? LogLevel::Info : LogLevel::Warning, message);
}
}

void setup() {
  Serial.begin(115200);
  logEvent_P(LogLevel::Info, PSTR("Xiaomi purifier monitor started"));
  WiFi.persistent(false); // Credentials live in LittleFS, never in SDK flash settings.
  const char* error;
  configured = loadConfig(config, error);
  oled.configure(config.oledAddress, config.sda, config.scl);
  display.begin();
  if (!configured) {
    WiFi.mode(WIFI_OFF);
    logEvent_P(LogLevel::Warning, PSTR("%s; opening setup"), error);
    management.begin(false, millis());
    return;
  }
  static Controller app(config.settings);
  logEvent_P(LogLevel::Info, PSTR("Configuration loaded; connecting Wi-Fi"));
  controller = &app;
  controller->begin(millis());
  display.message("CONNECTING WIFI");
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.begin(config.ssid, config.password);
  lastWifiTry = millis();
  management.begin(true, lastWifiTry);
}

void loop() {
  uint32_t now = millis();
  management.tick(now);
  now = millis();
  if (!configured) { delay(20); return; }
  if (WiFi.status() != WL_CONNECTED) {
    if (connected) { purifier.reset(); connected = false; }
    controller->setLink(LinkStatus::WifiDown, now);
    report(LinkStatus::WifiDown);
    if (elapsed(now, lastWifiTry, 10000)) {
      lastWifiTry = now;
      logEvent_P(LogLevel::Info, PSTR("Wi-Fi reconnect requested"));
      WiFi.reconnect();
    }
  } else {
    if (!connected) {
      connected = purifier.begin(config.deviceIp, config.token, config.settings, now);
      // Preserve an existing outage screen timer until an actual sample arrives.
      if (!connected) { controller->setLink(LinkStatus::Timeout, now); report(LinkStatus::Timeout); }
    }
    if (connected) {
      const auto event = purifier.tick(now);
      if (event == MiioClient::Event::Sample) {
        controller->accept(purifier.data(), now);
        report(LinkStatus::Ok);
        if (config.diagnostics) {
          const auto& d = purifier.data();
          logEvent_P(LogLevel::Info, PSTR("run_status=%s%lu rinse=%s%lu f1=%s%lu/%lu f2=%s%lu/%lu"),
              d.runStatusValid ? "" : "invalid:",
              static_cast<unsigned long>(d.runStatus), d.rinseValid ? "" : "invalid:",
              static_cast<unsigned long>(d.rinse), d.filters[0].valid ? "" : "invalid:",
              static_cast<unsigned long>(d.filters[0].used), static_cast<unsigned long>(d.filters[0].total),
              d.filters[1].valid ? "" : "invalid:", static_cast<unsigned long>(d.filters[1].used),
              static_cast<unsigned long>(d.filters[1].total));
        }
      } else if (event == MiioClient::Event::Error) {
        controller->setLink(purifier.error(), now);
        report(purifier.error());
      }
    }
  }
  if (!management.ownsDisplay(now) && elapsed(now, lastRender, 200)) {
    lastRender = now;
    display.show(controller->view(now));
  }
  delay(1);
}
