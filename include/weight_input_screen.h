#pragma once

#include <Arduino.h>
#include "controls.h"
#include "lsd.h"
#include "target_memory.h"
#include "weight_input.h"

class WeightInputScreen {
public:
  WeightInputScreen(Display& display, TargetMemory& targetMemory);
  void init();
  void enter();
  void exit();
  void loop();
  void handleEvent(ControlEvent event);

private:
  Display& display;
  TargetMemory& targetMemory;
  WeightInput input;
  bool initialized = false;
};
