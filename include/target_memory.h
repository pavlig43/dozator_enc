#pragma once

#include <Arduino.h>

// TargetMemory хранит последний подтверждённый целевой вес в EEPROM.
// Экран ввода читает его при первом входе и сохраняет только по CONFIRM.
class TargetMemory {
public:
  void init(); // Один раз загружает вес из EEPROM или оставляет значение по умолчанию.
  void save(unsigned long weight); // Сохраняет новый подтверждённый вес.
  unsigned long weight() const; // Текущая цель для рабочего экрана и дозирования.

private:
  unsigned long targetWeight = 50;
  bool initialized = false;
};
