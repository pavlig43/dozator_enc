#include <Arduino.h>
#include <EncButton.h>
#include "controls.h"
#include "pin_destination.h"

#define MENU_HOLD_TIME_MS 1000

EncButtonT<ENCODER_S1_PIN, ENCODER_S2_PIN, ENCODER_KEY_PIN> encoder;

void Controls::init() {
  encoder.init(INPUT_PULLUP, INPUT_PULLUP, LOW);
  encoder.setEncType(EB_STEP4_LOW);
  encoder.setEncReverse(false);
  encoder.setHoldTimeout(MENU_HOLD_TIME_MS);
}

ControlEvent Controls::read() {
  encoder.tick();

  if (encoder.hold()) {
    return ControlEvent::MENU;
  }

  if (encoder.click()) {
    return ControlEvent::SELECT;
  }

  if (encoder.left()) {
    return ControlEvent::LEFT;
  }

  if (encoder.right()) {
    return ControlEvent::RIGHT;
  }

  return ControlEvent::NONE;
}
