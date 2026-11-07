#include "Controller.h"

void Controller::begin(uint32_t now) { wakeAt_ = now; }

void Controller::accept(const PurifierData& data, uint32_t now) {
  const bool wasFresh = haveData_ && link_ == LinkStatus::Ok &&
      !elapsed(now, receivedAt_, settings_.staleAfterMs);
  if (!wasFresh) wakeAt_ = now;
  if (settings_.activitySource == ActivitySource::RunStatus && data.runStatusValid) {
    const bool making = (data.runStatus & settings_.makingMask) == settings_.makingValue;
    // Begin the full off-delay at the first observed stop, not at the last making poll.
    if (making || activity_ == Activity::Making) wakeAt_ = now;
    activity_ = making ? Activity::Making : Activity::Idle;
  } else if (settings_.activitySource == ActivitySource::FlowChange) {
    bool increased = false;
    for (size_t i = 0; i < 2; ++i) {
      increased |= wasFresh && data.filters[i].valid && data_.filters[i].valid &&
          data.filters[i].total == data_.filters[i].total &&
          data.filters[i].used > data_.filters[i].used;
    }
    if (increased) wakeAt_ = now;
    activity_ = Activity::FlowObserved; // Approximate activity, never labelled Making.
  } else {
    activity_ = Activity::Unknown;
  }
  data_ = data;
  haveData_ = true;
  receivedAt_ = now;
  link_ = LinkStatus::Ok;
}

void Controller::setLink(LinkStatus link, uint32_t now) {
  if (link_ != link && (link_ == LinkStatus::Ok || link_ == LinkStatus::Connecting)) wakeAt_ = now;
  link_ = link;
}

ViewModel Controller::view(uint32_t now) const {
  ViewModel v;
  v.data = data_;
  v.link = link_;
  v.fresh = haveData_ && link_ == LinkStatus::Ok && !elapsed(now, receivedAt_, settings_.staleAfterMs);
  if (link_ == LinkStatus::Ok && !v.fresh) v.link = LinkStatus::Timeout;
  v.activity = v.fresh ? activity_ : Activity::Unknown;
  v.awake = (v.fresh && (v.activity == Activity::Making || v.activity == Activity::Unknown)) ||
      !elapsed(now, wakeAt_, settings_.screenOffDelayMs);
  return v;
}
