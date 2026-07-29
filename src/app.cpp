#include <Arduino.h>
#include "app.h"

namespace {
const ScreenId MENU_ORDER[] = {
  ScreenId::WEIGHT_INPUT,
  ScreenId::FEED_SETTINGS,
  ScreenId::SCALE_CALIBRATION,
  ScreenId::WORK
};

const byte MENU_SCREEN_COUNT = sizeof(MENU_ORDER) / sizeof(MENU_ORDER[0]);
}

App::App()
  : dosing(scale, auger, targetMemory, feedMemory),
    weightInputScreen(display, targetMemory),
    feedSettingsScreen(display, feedMemory),
    scaleCalibrationScreen(display, scale),
    workScreen(display, scale, rgb, dosing, targetMemory) {
}

App& app() {
  static App instance;
  return instance;
}

void App::init() {
  display.init();
  controls.init();
  targetMemory.init();
  feedMemory.init();
  showMenu();
}

void App::loop() {
  const ControlEvent event = controls.read();

  if (menuActive) {
    handleMenuEvent(event);
    return;
  }

  if (event == ControlEvent::MENU) {
    openMenu(navigation.current());
    return;
  }

  handleEvent(event);
  loopCurrentScreen();
}

void App::handleEvent(ControlEvent event) {
  if (event == ControlEvent::NONE) {
    return;
  }

  switch (navigation.current()) {
  case ScreenId::WEIGHT_INPUT:
    weightInputScreen.handleEvent(event);
    break;

  case ScreenId::FEED_SETTINGS:
    feedSettingsScreen.handleEvent(event);
    break;

  case ScreenId::SCALE_CALIBRATION:
    scaleCalibrationScreen.handleEvent(event);
    break;

  case ScreenId::WORK:
    workScreen.handleEvent(event);
    break;
  }
}

void App::loopCurrentScreen() {
  switch (navigation.current()) {
  case ScreenId::WEIGHT_INPUT:
    weightInputScreen.loop();
    break;

  case ScreenId::FEED_SETTINGS:
    feedSettingsScreen.loop();
    break;

  case ScreenId::SCALE_CALIBRATION:
    scaleCalibrationScreen.loop();
    break;

  case ScreenId::WORK:
    workScreen.loop();
    break;
  }
}

void App::enterCurrentScreen() {
  switch (navigation.current()) {
  case ScreenId::WEIGHT_INPUT:
    weightInputScreen.enter();
    break;

  case ScreenId::FEED_SETTINGS:
    feedSettingsScreen.enter();
    break;

  case ScreenId::SCALE_CALIBRATION:
    scaleCalibrationScreen.enter();
    break;

  case ScreenId::WORK:
    workScreen.enter();
    break;
  }
}

void App::exitCurrentScreen() {
  switch (navigation.current()) {
  case ScreenId::WEIGHT_INPUT:
    weightInputScreen.exit();
    break;

  case ScreenId::FEED_SETTINGS:
    feedSettingsScreen.exit();
    break;

  case ScreenId::WORK:
    workScreen.exit();
    break;

  case ScreenId::SCALE_CALIBRATION:
    break;
  }
}

void App::showMenu() {
  display.showMenu(selectedScreen);
}

void App::handleMenuEvent(ControlEvent event) {
  if (event == ControlEvent::LEFT || event == ControlEvent::RIGHT) {
    selectMenuByEvent(event);
    showMenu();
  }
  else if (event == ControlEvent::SELECT) {
    openSelectedScreen();
  }
}

void App::openSelectedScreen() {
  menuActive = false;
  openScreen(selectedScreen);
}

void App::openScreen(ScreenId screen) {
  if (screen == navigation.current()) {
    enterCurrentScreen();
    return;
  }

  navigation.open(screen);
  navigation.commit();
  selectedScreen = navigation.current();
  enterCurrentScreen();
}

void App::openMenu(ScreenId screen) {
  exitCurrentScreen();
  selectedScreen = screen;
  menuActive = true;
  showMenu();
}

void App::selectMenuByEvent(ControlEvent event) {
  selectedScreen = menuScreenByEvent(selectedScreen, event);
}

ScreenId App::menuScreenByEvent(ScreenId screen, ControlEvent event) {
  for (byte i = 0; i < MENU_SCREEN_COUNT; i++) {
    if (MENU_ORDER[i] == screen) {
      if (event == ControlEvent::LEFT) {
        return MENU_ORDER[(i + MENU_SCREEN_COUNT - 1) % MENU_SCREEN_COUNT];
      }

      return MENU_ORDER[(i + 1) % MENU_SCREEN_COUNT];
    }
  }

  return ScreenId::WEIGHT_INPUT;
}
