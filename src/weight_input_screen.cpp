#include "weight_input_screen.h"

WeightInputScreen::WeightInputScreen(Display& display, TargetMemory& targetMemory)
  : display(display),
    targetMemory(targetMemory) {
}

void WeightInputScreen::init() {
  if (initialized) {
    return;
  }

  targetMemory.init();
  input.setTargetWeight(targetMemory.weight());
  initialized = true;
}

void WeightInputScreen::enter() {
  init();
  display.showWeightInput(input.targetWeight());
}

void WeightInputScreen::exit() {
  targetMemory.save(input.targetWeight());
}

void WeightInputScreen::loop() {
}

void WeightInputScreen::handleEvent(ControlEvent event) {
  const unsigned long oldValue = input.targetWeight();
  input.handleEvent(event);

  if (input.targetWeight() != oldValue) {
    display.showWeightInput(input.targetWeight());
  }
}
