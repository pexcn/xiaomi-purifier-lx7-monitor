#pragma once
#include "Model.h"

class Controller {
 public:
  explicit Controller(const Settings& settings) : settings_(settings) {}
  void begin(uint32_t now);
  void accept(const PurifierData& data, uint32_t now);
  void setLink(LinkStatus link, uint32_t now);
  ViewModel view(uint32_t now) const;
 private:
  Settings settings_;
  PurifierData data_;
  LinkStatus link_ = LinkStatus::Connecting;
  Activity activity_ = Activity::Unknown;
  bool haveData_ = false;
  uint32_t receivedAt_ = 0, wakeAt_ = 0;
};
