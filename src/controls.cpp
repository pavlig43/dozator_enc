#include <Arduino.h>
#include <EncButton.h>
#include "controls.h"

/**
 * Подключение энкодера:
 * - S1  -> D8;
 * - S2  -> D9;
 * - KEY -> D10;
 * - "+" -> 5V;
 * - "-" -> GND.
 *
 * Подключение кнопки MENU без фиксации:
 * - первый вывод -> D4;
 * - второй вывод -> GND.
 *
 * Входы работают как INPUT_PULLUP: отпущенная кнопка читается как HIGH.
 * При нажатии контакт замыкается на GND, пин читается как LOW,
 * и библиотека считает кнопку нажатой.
 */
#define ENCODER_S1_PIN 8
#define ENCODER_S2_PIN 9
#define ENCODER_KEY_PIN 10
#define MENU_BUTTON_PIN 4

EncButtonT<ENCODER_S1_PIN, ENCODER_S2_PIN, ENCODER_KEY_PIN> encoder;
ButtonT<MENU_BUTTON_PIN> menuButton;

void Controls::init() {
  encoder.init(INPUT_PULLUP, INPUT_PULLUP, LOW);
  encoder.setEncType(EB_STEP4_LOW);
  encoder.setEncReverse(false);

  menuButton.init(INPUT_PULLUP);
  menuButton.setBtnLevel(LOW);
}

ControlEvent Controls::read() {
  encoder.tick();
  menuButton.tick();

  if (menuButton.press()) {
    return ControlEvent::MENU;
  }

  if (encoder.press()) {
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
