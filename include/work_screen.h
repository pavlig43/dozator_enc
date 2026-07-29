#pragma once

#include <Arduino.h>
#include "controls.h"
#include "dosing_controller.h"
#include "lsd.h"
#include "rgb_led.h"
#include "scale_sensor.h"
#include "target_memory.h"
#include "tmr.h"

class WorkScreen {
public:
  WorkScreen(Display& display, Scale& scale, Rgb& rgb, DosingController& dosing, TargetMemory& targetMemory);
  void enter();
  void exit();
  void loop();
  void handleEvent(ControlEvent event);

private:
  Display& display;
  Scale& scale;
  Rgb& rgb;
  DosingController& dosing;
  TargetMemory& targetMemory;
  bool initialized = false;
  bool tarePending = false;
  Tmr weightScreenTimer;

  void init();
  void beginTareAndStart();
  void finishTare();
  void updateRgb();
};
