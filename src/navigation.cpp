#include "navigation.h"

void Navigation::open(ScreenId screen) {
  requestedScreen = screen;
}

ScreenId Navigation::current() const {
  return currentScreen;
}

bool Navigation::hasPendingChange() const {
  return requestedScreen != currentScreen;
}

void Navigation::commit() {
  currentScreen = requestedScreen;
}
