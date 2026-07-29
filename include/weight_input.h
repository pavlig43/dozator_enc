#pragma once

#include <Arduino.h>
#include "controls.h"

class WeightInput {
public:
  void setTargetWeight(unsigned long weight);
  void handleEvent(ControlEvent event);
  unsigned long targetWeight() const;

private:
  static const long MIN_TARGET_GRAMS = 50L;
  static const long MAX_TARGET_GRAMS = 99950L;
  static const long TARGET_STEP_GRAMS = 50L;

  unsigned long value = MIN_TARGET_GRAMS;

  static unsigned long normalize(unsigned long weight);
};
