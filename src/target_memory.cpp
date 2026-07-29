#include <Arduino.h>
#include <EEPROM.h>
#include "target_memory.h"

// EEPROM-карта целевого веса:
// 4    - marker, признак корректно сохранённого веса.
// 5..8 - unsigned long с последним подтверждённым целевым весом.
#define EEPROM_TARGET_MARKER_ADDRESS 4
#define EEPROM_TARGET_VALUE_ADDRESS 5
#define EEPROM_TARGET_MARKER 0x5A

void TargetMemory::init() {
  if (initialized) {
    return;
  }

  if (EEPROM.read(EEPROM_TARGET_MARKER_ADDRESS) != EEPROM_TARGET_MARKER) {
    targetWeight = 50;
    initialized = true;
    return;
  }

  EEPROM.get(EEPROM_TARGET_VALUE_ADDRESS, targetWeight);

  if (targetWeight > 99999UL) {
    targetWeight = 50UL;
  }

  targetWeight = normalize(targetWeight);
  initialized = true;
}

void TargetMemory::save(unsigned long weight) {
  targetWeight = normalize(weight);
  EEPROM.put(EEPROM_TARGET_VALUE_ADDRESS, targetWeight);
  EEPROM.update(EEPROM_TARGET_MARKER_ADDRESS, EEPROM_TARGET_MARKER);
}

unsigned long TargetMemory::weight() const {
  return targetWeight;
}

unsigned long TargetMemory::normalize(unsigned long weight) {
  const unsigned long clamped = constrain(weight, MIN_TARGET_GRAMS, MAX_TARGET_GRAMS);
  return ((clamped + TARGET_STEP_GRAMS / 2) / TARGET_STEP_GRAMS) * TARGET_STEP_GRAMS;
}
