#pragma once
#include "Config.h"
#include <ArduinoJson.h>

bool parseConfig(JsonVariantConst doc, Config& config, const char*& error);
void configToJson(JsonDocument& doc, const Config& config, bool includeSecrets);
bool mergeConfigUpdate(JsonVariantConst update, const Config& current, Config& out, const char*& error);
