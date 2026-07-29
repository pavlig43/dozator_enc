#pragma once

#include <Arduino.h>

enum class ControlEvent : byte {
  NONE,
  LEFT,
  RIGHT,
  SELECT,
  MENU
};

class Controls {
public:
  void init();
  ControlEvent read();
};
