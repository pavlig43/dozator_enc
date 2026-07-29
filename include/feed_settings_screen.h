#pragma once

#include <Arduino.h>
#include "controls.h"
#include "feed_memory.h"
#include "lsd.h"

class FeedSettingsScreen {
public:
  FeedSettingsScreen(Display& display, FeedMemory& memory);
  void enter();
  void exit();
  void loop();
  void handleEvent(ControlEvent event);

private:
  Display& display;
  FeedMemory& memory;
  unsigned int value = 50;
};
