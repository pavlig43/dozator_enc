#include <Arduino.h>
#include "weight_input.h"

void WeightInput::setTargetWeight(unsigned long weight) {
  value = normalize(weight);
}

void WeightInput::handleEvent(ControlEvent event) {
  long nextValue = (long)value;

  if (event == ControlEvent::LEFT) {
    nextValue -= TARGET_STEP_GRAMS;
  }
  else if (event == ControlEvent::RIGHT) {
    nextValue += TARGET_STEP_GRAMS;
  }
  else {
    return;
  }

  value = constrain(nextValue, MIN_TARGET_GRAMS, MAX_TARGET_GRAMS);
}

unsigned long WeightInput::targetWeight() const {
  return value;
}

unsigned long WeightInput::normalize(unsigned long weight) {
  const unsigned long clamped = constrain(
    weight,
    (unsigned long)MIN_TARGET_GRAMS,
    (unsigned long)MAX_TARGET_GRAMS
  );
  return ((clamped + TARGET_STEP_GRAMS / 2) / TARGET_STEP_GRAMS) * TARGET_STEP_GRAMS;
}
