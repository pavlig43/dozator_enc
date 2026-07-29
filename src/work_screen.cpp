#include "work_screen.h"

#define WEIGHT_SCREEN_UPDATE_MS 200UL

WorkScreen::WorkScreen(
  Display& display,
  Scale& scale,
  Rgb& rgb,
  DosingController& dosing,
  TargetMemory& targetMemory
)
  : display(display),
    scale(scale),
    rgb(rgb),
    dosing(dosing),
    targetMemory(targetMemory),
    weightScreenTimer(WEIGHT_SCREEN_UPDATE_MS) {
}

void WorkScreen::init() {
  if (initialized) {
    return;
  }

  scale.init();
  rgb.init();
  dosing.init();
  initialized = true;
}

void WorkScreen::enter() {
  init();
  display.showWork(scale.weightGrams(), targetMemory.weight(), !dosing.isDosing());
  weightScreenTimer.reset();
  updateRgb();
}

void WorkScreen::exit() {
  tarePending = false;
  dosing.stop();
  rgb.off();
}

void WorkScreen::loop() {
  scale.loop();

  if (tarePending) {
    updateRgb();

    if (scale.tareDone()) {
      finishTare();
    }

    return;
  }

  dosing.loop();
  updateRgb();

  if (weightScreenTimer.ready()) {
    display.updateCurrentWeight(scale.weightGrams(), !dosing.isDosing());
  }
}

void WorkScreen::handleEvent(ControlEvent event) {
  if (event == ControlEvent::SELECT) {
    beginTareAndStart();
  }
}

void WorkScreen::beginTareAndStart() {
  dosing.stop();
  display.showTare();
  scale.requestTare();
  tarePending = true;
}

void WorkScreen::finishTare() {
  tarePending = false;
  dosing.start();
  display.showWork(scale.weightGrams(), targetMemory.weight(), false);
  weightScreenTimer.reset();
}

void WorkScreen::updateRgb() {
  if (dosing.isDosing()) {
    rgb.dosing();
  }
  else {
    rgb.ready();
  }
}
