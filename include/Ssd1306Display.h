#pragma once
#include "Display.h"
#include <U8g2lib.h>

class Ssd1306Display final : public Display {
 public:
  explicit Ssd1306Display(const Settings& settings) : settings_(settings) {}
  void configure(uint8_t address, uint8_t sda, uint8_t scl);
  void begin() override;
  void show(const ViewModel& model) override;
  void message(const char* text) override;
  void setupAccess(const char* ssid, const char* password, const char* ip) override;
  void setAwake(bool awake) override;
 private:
  void drawLines(const char* a, const char* b, const char* c, const char* d);
  const Settings& settings_;
  U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C oled_{U8G2_R0, U8X8_PIN_NONE};
  uint8_t address_ = 0x3c, sda_ = 4, scl_ = 5;
  bool awake_ = true;
};
