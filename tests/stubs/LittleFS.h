#pragma once
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <map>
#include <string>

struct LittleFSConfig { explicit LittleFSConfig(bool value = true) : autoFormat(value) {} bool autoFormat; };
struct TestFile {
  std::string* data = nullptr;
  size_t offset = 0;
  explicit operator bool() const { return data != nullptr; }
  size_t size() const { return data ? data->size() : 0; }
  int read() { return data && offset < data->size() ? uint8_t((*data)[offset++]) : -1; }
  size_t readBytes(char* out, size_t n) {
    n = data ? std::min(n, data->size() - offset) : 0;
    if (n) memcpy(out, data->data() + offset, n);
    offset += n;
    return n;
  }
  size_t write(uint8_t c) { return write(&c, 1); }
  size_t write(const uint8_t* p, size_t n) {
    if (!data) return 0;
    data->append(reinterpret_cast<const char*>(p), n);
    return n;
  }
  void flush() {}
  void close() { data = nullptr; }
};
struct TestLittleFS {
  bool available = false, autoFormat = true, failRename = false;
  unsigned formatCalls = 0;
  std::map<std::string, std::string> files;
  void setConfig(const LittleFSConfig& c) { autoFormat = c.autoFormat; }
  bool begin() { return available; }
  bool format() { ++formatCalls; files.clear(); available = true; return true; }
  TestFile open(const char* path, const char* mode) {
    if (!available) return {};
    if (*mode == 'w') files[path].clear();
    auto it = files.find(path);
    return it == files.end() ? TestFile{} : TestFile{&it->second, 0};
  }
  bool rename(const char* from, const char* to) {
    auto it = files.find(from);
    if (failRename || it == files.end()) return false;
    files[to] = it->second;
    files.erase(it);
    return true;
  }
  void remove(const char* path) { files.erase(path); }
};
inline TestLittleFS LittleFS;
