#include "Ssd1306Display.h"
#include <Wire.h>
#include <cmath>
#include <cstdio>

namespace {
const char* linkText(LinkStatus status) {
  switch (status) {
    case LinkStatus::Connecting: return "CONNECTING";
    case LinkStatus::WifiDown: return "WIFI DISCONNECTED";
    case LinkStatus::Timeout: return "MIIO TIMEOUT";
    case LinkStatus::InvalidPacket: return "MIIO CHECK FAILED";
    case LinkStatus::RpcError: return "MIIO RPC ERROR";
    case LinkStatus::BadData: return "INVALID DATA";
    default: return "WAITING FOR DATA";
  }
}
void countText(char* out, size_t cap, bool valid, uint32_t n) {
  if (valid) snprintf(out, cap, "%lu", static_cast<unsigned long>(n));
  else snprintf(out, cap, "--");
}
void filterText(char* out, size_t cap, const FilterFlow& f, const Settings& s, size_t i) {
  const int percent = remainingPercent(f);
  if (s.filterDisplay == FilterDisplay::Percent) {
    if (percent < 0) snprintf(out, cap, "--%%");
    else snprintf(out, cap, "%d%%", percent);
  } else {
    const double litres = remainingFlow(f) * static_cast<double>(s.litresPerFlowUnit[i]);
    if (percent < 0 || s.litresPerFlowUnit[i] <= 0 || !std::isfinite(litres)) snprintf(out, cap, "--L?");
    else if (litres > 999999) snprintf(out, cap, ">999999L");
    else snprintf(out, cap, "%.0fL", std::floor(litres));
  }
}
}

void Ssd1306Display::configure(uint8_t address, uint8_t sda, uint8_t scl) {
  address_ = address; sda_ = sda; scl_ = scl;
}
void Ssd1306Display::begin() {
  u8x8_SetPin_HW_I2C(oled_.getU8x8(), U8X8_PIN_NONE, scl_, sda_);
  oled_.setI2CAddress(address_ << 1); // U8g2 expects the 8-bit bus address.
  oled_.begin();
  oled_.setFont(u8g2_font_5x7_tr);
}
void Ssd1306Display::setAwake(bool awake) {
  if (awake == awake_) return;
  awake_ = awake;
  oled_.setPowerSave(awake ? 0 : 1);
}
void Ssd1306Display::drawLines(const char* a, const char* b, const char* c, const char* d) {
  oled_.firstPage();
  do {
    oled_.drawStr(0, 7, a); oled_.drawStr(0, 15, b);
    oled_.drawStr(0, 23, c); oled_.drawStr(0, 31, d);
  } while (oled_.nextPage());
}
void Ssd1306Display::message(const char* text) {
  setAwake(true);
  drawLines("MI PURIFIER LX7", text, "", "See README / Serial");
}
void Ssd1306Display::setupAccess(const char* ssid, const char* password, const char* ip) {
  setAwake(true);
  char key[32];
  snprintf(key, sizeof(key), "KEY: %s", password);
  drawLines("WIFI SETUP", ssid, key, ip);
}
void Ssd1306Display::show(const ViewModel& v) {
  setAwake(v.awake);
  if (!v.awake) return;
  if (!v.fresh) {
    drawLines("MI PURIFIER LX7", linkText(v.link), "DATA UNAVAILABLE", "Retrying automatically");
    return;
  }
  char a[64], b[64], c[64], in[12], out[12], f1[16], f2[16], temp[16];
  countText(in, sizeof(in), v.data.tdsInValid, v.data.tdsIn);
  countText(out, sizeof(out), v.data.tdsOutValid, v.data.tdsOut);
  filterText(f1, sizeof(f1), v.data.filters[0], settings_, 0);
  filterText(f2, sizeof(f2), v.data.filters[1], settings_, 1);
  if (v.data.temperatureValid) snprintf(temp, sizeof(temp), "%.1f", v.data.temperature);
  else snprintf(temp, sizeof(temp), "--");
  snprintf(a, sizeof(a), "IN:%s OUT:%s ppm", in, out);
  snprintf(b, sizeof(b), "F1:%s F2:%s", f1, f2);
  snprintf(c, sizeof(c), "T:%sC", temp);
  drawLines(a, b, c, "");
}
