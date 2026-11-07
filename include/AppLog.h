#pragma once
#include "RuntimeLog.h"

extern RuntimeLog monitorLog;
// Updated from the main loop, so millis() wrap does not reset uptime or timestamps.
uint64_t monitorUptimeMs();
// Call with fixed messages and non-secret numeric data only. Never log request bodies,
// passwords, purifier tokens, session cookies, CSRF values or the setup AP key.
void logEvent_P(LogLevel level, const char* format, ...) __attribute__((format(printf, 2, 3)));
