#include "AppLog.h"
#include <Arduino.h>
#include <cstdarg>
#include <cstdio>

RuntimeLog monitorLog;

uint64_t monitorUptimeMs() {
  static uint32_t previous = 0;
  static uint64_t total = 0;
  const uint32_t now = millis();
  total += uint32_t(now - previous);
  previous = now;
  return total;
}

void logEvent_P(LogLevel level, const char* format, ...) {
  char message[160];
  va_list args;
  va_start(args, format);
  vsnprintf_P(message, sizeof(message), format, args);
  va_end(args);
  const uint64_t now = monitorUptimeMs();
  monitorLog.append(now, level, message);
  Serial.printf_P(PSTR("[%llu.%03u] %s %s\n"), static_cast<unsigned long long>(now / 1000),
      static_cast<unsigned>(now % 1000), logLevelText(level), message);
}
