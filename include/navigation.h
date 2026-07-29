#pragma once

#include <Arduino.h>

enum class ScreenId : byte {
  WEIGHT_INPUT,
  FEED_SETTINGS,
  SCALE_CALIBRATION,
  WORK
};

// Navigation stores the active screen and the screen selected in the menu.
class Navigation {
public:
  void open(ScreenId screen); // Запросить переход на конкретный экран.
  ScreenId current() const; // Экран, который сейчас реально активен.
  bool hasPendingChange() const; // Есть ли запрошенный, но ещё не применённый переход.
  void commit(); // Сделать запрошенный экран текущим.

private:
  ScreenId currentScreen = ScreenId::WORK;
  ScreenId requestedScreen = ScreenId::WORK;
};
