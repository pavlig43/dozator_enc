#include "feed_settings_screen.h"

FeedSettingsScreen::FeedSettingsScreen(Display& display, FeedMemory& memory)
  : display(display),
    memory(memory) {
}

void FeedSettingsScreen::enter() {
  memory.init();
  value = memory.stopMarginGrams();
  display.showFeedSettings(value);
}

void FeedSettingsScreen::exit() {
  memory.setStopMarginGrams(value);
  memory.save();
}

void FeedSettingsScreen::loop() {
}

void FeedSettingsScreen::handleEvent(ControlEvent event) {
  if (event == ControlEvent::LEFT) {
    value = constrain((long)value - 1L, 1L, 999L);
  }
  else if (event == ControlEvent::RIGHT) {
    value = constrain((long)value + 1L, 1L, 999L);
  }
  else {
    return;
  }

  display.showFeedSettings(value);
}
