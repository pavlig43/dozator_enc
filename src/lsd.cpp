#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "lsd.h"
#include "pin_destination.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

void Display::init() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  showLoading();
}

void Display::showLoading() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Loading...");
}

void Display::showMenu(ScreenId selectedScreen) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select screen");
  lcd.setCursor(0, 1);

  if (selectedScreen == ScreenId::WEIGHT_INPUT) {
    lcd.print("> Weight input");
  }
  else if (selectedScreen == ScreenId::FEED_SETTINGS) {
    lcd.print("> Feed setup");
  }
  else if (selectedScreen == ScreenId::SCALE_CALIBRATION) {
    lcd.print("> Calibration");
  }
  else {
    lcd.print("> Work");
  }
}

void Display::showTare() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tare...");
}

void Display::showScaleCalibrationStart() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press encoder");
  lcd.setCursor(0, 1);
  lcd.print("to zero");
}

void Display::showScaleCalibrationWeight() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Put 1kg");
  lcd.setCursor(0, 1);
  lcd.print("wait...");
}

void Display::showScaleCalibrationDone() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("OK saved");
  lcd.setCursor(0, 1);
  lcd.print("Press to exit");
}

void Display::showWeightInput(unsigned long targetWeight) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Target weight, g");
  lcd.setCursor(0, 1);
  lcd.print(targetWeight);
}

void Display::showFeedSettings(unsigned int stopMarginGrams) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Stop weight, g");
  lcd.setCursor(0, 1);
  lcd.print(stopMarginGrams);
}

void Display::showWork(long currentWeight, unsigned long targetWeight, bool showStartHint) {
  lcd.clear();
  updateCurrentWeight(currentWeight, showStartHint);
  lcd.setCursor(0, 1);
  lcd.print("Target ");
  lcd.print(targetWeight);
}

void Display::updateCurrentWeight(long currentWeight, bool showStartHint) {
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);

  if (showStartHint) {
    lcd.print("PUSH ");
  }

  lcd.print(currentWeight);
}
