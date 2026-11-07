#include "RuntimeLog.h"
#include <algorithm>
#include <cstdio>
#include <cstring>

const char* logLevelText(LogLevel level) {
  switch (level) {
    case LogLevel::Warning: return "WARN";
    case LogLevel::Error: return "ERROR";
    default: return "INFO";
  }
}

void RuntimeLog::append(uint64_t now, LogLevel level, const char* message) {
  char line[192];
  size_t n = snprintf(line, sizeof(line), "[%llu.%03u] %s ",
      static_cast<unsigned long long>(now / 1000), static_cast<unsigned>(now % 1000), logLevelText(level));
  if (message) {
    for (; *message && n < sizeof(line) - 1; ++message) {
      const unsigned char c = *message;
      line[n++] = c < 32 ? ' ' : c;
    }
    // If a UTF-8 character was cut off, discard its leading/continuation bytes.
    if (*message && (static_cast<unsigned char>(*message) & 0xc0) == 0x80) {
      while (n && (static_cast<unsigned char>(line[n - 1]) & 0xc0) == 0x80) --n;
      if (n) --n;
    }
  }
  line[n++] = '\n';
  while (size_ + n > Capacity) {
    char removed;
    do { removed = data_[head_]; head_ = (head_ + 1) % Capacity; --size_; }
    while (size_ && removed != '\n');
  }
  for (size_t i = 0; i < n; ++i) data_[(head_ + size_ + i) % Capacity] = line[i];
  size_ += n;
}

size_t RuntimeLog::read(size_t offset, char* out, size_t capacity) const {
  if (!out || offset >= size_) return 0;
  const size_t n = std::min(capacity, size_ - offset);
  const size_t start = (head_ + offset) % Capacity;
  const size_t first = std::min(n, Capacity - start);
  memcpy(out, data_ + start, first);
  memcpy(out + first, data_, n - first);
  return n;
}
