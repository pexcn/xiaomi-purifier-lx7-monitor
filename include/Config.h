#pragma once
#include "Model.h"

struct Config {
  char ssid[33] = {};
  char password[65] = {};
  char deviceIp[16] = {};
  char token[33] = {};
  char adminPassword[65] = {}; // Empty only for migration from the original firmware.
  Settings settings;
  bool diagnostics = false;
  uint8_t oledAddress = 0x3c;
  uint8_t sda = 4, scl = 5; // NodeMCU D2, D1
};

// Mount with auto-format disabled; initialization is an explicit action in the setup page.
bool loadConfig(Config& config, const char*& error);
bool configStorageReady();
bool saveConfig(const Config& config, bool initializeStorage, const char*& error);
