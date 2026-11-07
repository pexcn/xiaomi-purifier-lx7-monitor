#pragma once
#include "Model.h"

struct Config {
  char ssid[33] = {};
  char password[65] = {};
  char deviceIp[16] = {};
  char token[33] = {};
  Settings settings;
  bool diagnostics = false;
  uint8_t oledAddress = 0x3c;
  uint8_t sda = 4, scl = 5; // NodeMCU D2, D1
};

// No formatting on mount failure; never print credential values.
bool loadConfig(Config& config, const char*& error);
