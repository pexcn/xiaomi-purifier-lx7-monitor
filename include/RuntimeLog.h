#pragma once
#include <cstddef>
#include <cstdint>

enum class LogLevel { Info, Warning, Error };
const char* logLevelText(LogLevel level);

// Whole-line ring buffer, used only on the main loop. No heap or flash writes.
class RuntimeLog {
 public:
  static constexpr size_t Capacity = 2048;
  void append(uint64_t now, LogLevel level, const char* message);
  size_t size() const { return size_; }
  // Copies raw bytes, without a terminating NUL, in chronological order.
  size_t read(size_t offset, char* out, size_t capacity) const;
 private:
  char data_[Capacity] = {};
  size_t head_ = 0, size_ = 0;
};
