#pragma once

#include <Arduino.h>
#include "auger_motor.h"
#include "feed_memory.h"
#include "scale_sensor.h"
#include "target_memory.h"
#include "tmr.h"

class DosingController {
public:
  DosingController(Scale& scale, AugerMotor& auger, TargetMemory& targetMemory, FeedMemory& feedMemory);
  void init();
  void loop();
  void start();
  void stop();
  bool isDosing() const;

private:
  enum class State : byte {
    IDLE,
    MAIN_FILL,
    WAIT,
    SLOW_FILL
  };

  Scale& scale;
  AugerMotor& auger;
  TargetMemory& targetMemory;
  FeedMemory& feedMemory;
  State state = State::IDLE;
  Tmr waitTimer;
  Tmr slowFillTimer;

  void setState(State nextState);
};
