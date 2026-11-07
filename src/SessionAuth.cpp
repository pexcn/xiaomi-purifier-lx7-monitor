#include "SessionAuth.h"
#include "Model.h"
#include <cstring>

namespace {
bool sameToken(const char* a, const char* b) {
  uint8_t diff = 0;
  for (size_t i = 0; i < 32; ++i) diff |= static_cast<uint8_t>(a[i] ^ b[i]);
  return diff == 0;
}
}

bool passwordMatches(const char* provided, const char* configured) {
  if (!provided || !configured || !*configured) return false;
  const size_t n = strlen(configured);
  if (strlen(provided) != n) return false;
  uint8_t diff = 0;
  for (size_t i = 0; i < n; ++i) diff |= static_cast<uint8_t>(provided[i] ^ configured[i]);
  return diff == 0;
}

bool SessionAuth::readCookie(const char* p, char token[33]) {
  if (!p) return false;
  bool found = false;
  while (*p) {
    while (*p == ' ' || *p == '\t' || *p == ';') ++p;
    const char* end = strchr(p, ';');
    if (!end) end = p + strlen(p);
    const char* equals = static_cast<const char*>(memchr(p, '=', end - p));
    if (equals && size_t(equals - p) == strlen(CookieName) && !memcmp(p, CookieName, equals - p)) {
      const char* valueEnd = end;
      while (valueEnd > equals + 1 && (valueEnd[-1] == ' ' || valueEnd[-1] == '\t')) --valueEnd;
      if (found || valueEnd - equals - 1 != 32) return false;
      memcpy(token, equals + 1, 32);
      token[32] = 0;
      found = true;
    }
    p = *end ? end + 1 : end;
  }
  return found;
}

bool SessionAuth::create(const char* token, uint32_t now) {
  if (!token || strlen(token) != 32) return false;
  size_t selected = 0;
  for (size_t i = 0; i < 2; ++i) {
    if (!sessions_[i].token[0] || elapsed(now, sessions_[i].lastSeen, IdleTimeoutMs)) { selected = i; break; }
    if (uint32_t(now - sessions_[i].lastSeen) > uint32_t(now - sessions_[selected].lastSeen)) selected = i;
  }
  memcpy(sessions_[selected].token, token, 33);
  sessions_[selected].lastSeen = now;
  return true;
}

bool SessionAuth::accept(const char* header, uint32_t now) {
  char token[33];
  if (!readCookie(header, token)) return false;
  for (auto& s : sessions_) {
    if (!s.token[0]) continue;
    if (elapsed(now, s.lastSeen, IdleTimeoutMs)) { s.token[0] = 0; continue; }
    if (sameToken(s.token, token)) { s.lastSeen = now; return true; }
  }
  return false;
}

void SessionAuth::logout(const char* header) {
  char token[33];
  if (!readCookie(header, token)) return;
  for (auto& s : sessions_) if (s.token[0] && sameToken(s.token, token)) s.token[0] = 0;
}
