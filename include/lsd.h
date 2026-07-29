#pragma once

#include <Arduino.h>
#include "navigation.h"

class Display {
public:
  void init();
  void showLoading();
  void showMenu(ScreenId selectedScreen);
  void showTare();
  void showScaleCalibrationStart();
  void showScaleCalibrationWeight();
  void showScaleCalibrationDone();
  void showWeightInput(unsigned long targetWeight);
  void showFeedSettings(unsigned int stopMarginGrams);
  void showWork(long currentWeight, unsigned long targetWeight, bool showStartHint);
  void updateCurrentWeight(long currentWeight, bool showStartHint);
};
