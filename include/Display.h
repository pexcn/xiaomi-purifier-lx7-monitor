#pragma once
#include "Model.h"

// Add an ST7789/ILI9341 implementation without changing MiIO or Controller.
class Display {
 public:
  virtual ~Display() = default;
  virtual void begin() = 0;
  virtual void show(const ViewModel& model) = 0;
  virtual void message(const char* text) = 0;
  virtual void setupAccess(const char* ssid, const char* password, const char* ip) = 0;
  virtual void setAwake(bool awake) = 0;
};
