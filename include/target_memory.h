#pragma once

#include <Arduino.h>

// TargetMemory stores the target weight in EEPROM.
class TargetMemory {
public:
  void init(); // Один раз загружает вес из EEPROM или оставляет значение по умолчанию.
  void save(unsigned long weight); // Сохраняет новый подтверждённый вес.
  unsigned long weight() const; // Текущая цель для рабочего экрана и дозирования.

private:
  static const unsigned long MIN_TARGET_GRAMS = 50UL;
  static const unsigned long MAX_TARGET_GRAMS = 99950UL;
  static const unsigned long TARGET_STEP_GRAMS = 50UL;

  unsigned long targetWeight = 50;
  bool initialized = false;

  static unsigned long normalize(unsigned long weight);
};
