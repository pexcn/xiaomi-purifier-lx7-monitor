#pragma once
#include <cstddef>
#include <cstdint>

enum class ActivitySource { Unverified, RunStatus, FlowChange, TdsChange };
enum class FilterDisplay { Percent, Litres };
enum class Activity { Unknown, Idle, Making, FlowObserved, TdsObserved };
enum class LinkStatus { Connecting, Ok, WifiDown, Timeout, InvalidPacket, RpcError, BadData };

struct FilterFlow {
  uint32_t used = 0;
  uint32_t total = 0;
  bool valid = false;
};

struct PurifierData {
  uint32_t tdsIn = 0, tdsOut = 0, runStatus = 0, rinse = 0;
  bool tdsInValid = false, tdsOutValid = false, runStatusValid = false, rinseValid = false;
  float temperature = 0;
  bool temperatureValid = false;
  FilterFlow filters[2];
};

struct Settings {
  uint32_t pollIntervalMs = 2500;
  uint32_t screenOffDelayMs = 30000;
  uint32_t responseTimeoutMs = 1500;
  uint32_t staleAfterMs = 10000;
  FilterDisplay filterDisplay = FilterDisplay::Percent;
  float litresPerFlowUnit[2] = {0, 0}; // 0 means conversion has not been verified.
  ActivitySource activitySource = ActivitySource::TdsChange;
  uint32_t makingMask = 0, makingValue = 0;
};

struct ViewModel {
  PurifierData data;
  LinkStatus link = LinkStatus::Connecting;
  Activity activity = Activity::Unknown;
  bool fresh = false;
  bool awake = true;
};

// Unsigned subtraction remains valid across millis() wraparound.
inline bool elapsed(uint32_t now, uint32_t since, uint32_t duration) {
  return static_cast<uint32_t>(now - since) >= duration;
}

inline uint32_t remainingFlow(const FilterFlow& f) {
  return f.used >= f.total ? 0 : f.total - f.used;
}

inline int remainingPercent(const FilterFlow& f) {
  return !f.valid || f.total == 0 ? -1 :
      static_cast<int>(static_cast<uint64_t>(remainingFlow(f)) * 100 / f.total);
}
