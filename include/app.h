#pragma once

#include <Arduino.h>
#include "auger_motor.h"
#include "controls.h"
#include "dosing_controller.h"
#include "feed_memory.h"
#include "feed_settings_screen.h"
#include "lsd.h"
#include "navigation.h"
#include "rgb_led.h"
#include "scale_calibration_screen.h"
#include "scale_sensor.h"
#include "target_memory.h"
#include "weight_input_screen.h"
#include "work_screen.h"

class App {
public:
  App();
  void init();
  void loop();

private:
  Controls controls;
  Display display;
  Scale scale;
  AugerMotor auger;
  Rgb rgb;
  FeedMemory feedMemory;
  TargetMemory targetMemory;
  Navigation navigation;

  DosingController dosing;
  WeightInputScreen weightInputScreen;
  FeedSettingsScreen feedSettingsScreen;
  ScaleCalibrationScreen scaleCalibrationScreen;
  WorkScreen workScreen;
  bool menuActive = true;
  ScreenId selectedScreen = ScreenId::WORK;

  void handleEvent(ControlEvent event);
  void loopCurrentScreen();
  void enterCurrentScreen();
  void exitCurrentScreen();
  void showMenu();
  void handleMenuEvent(ControlEvent event);
  void openSelectedScreen();
  void openScreen(ScreenId screen);
  void openMenu(ScreenId screen);
  void selectMenuByEvent(ControlEvent event);
  static ScreenId menuScreenByEvent(ScreenId screen, ControlEvent event);
};

App& app();
