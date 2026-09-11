#pragma once

// ATmega328P: номера совместимы с нумерацией Arduino Nano.

#define SCALE_DT_PIN 9
#define SCALE_SCK_PIN 10

#define RGB_RED_PIN 11
#define RGB_GREEN_PIN 12
#define RGB_BLUE_PIN 13

// Нажимной энкодер:
// S1  -> D7
// S2  -> D6
// KEY -> D5
// +   -> 5V
// -   -> GND
#define ENCODER_S1_PIN 7
#define ENCODER_S2_PIN 6
#define ENCODER_KEY_PIN 5

// Входы DRV8871 для двигателя шнека:
// IN1 -> D2
// IN2 -> D3
#define AUGER_IN1_PIN 2
#define AUGER_IN2_PWM_PIN 3

// LCD 16x2 с I2C-переходником:
// SDA -> A4 / SDA
// SCL -> A5 / SCL
// VCC -> 5V
// GND -> GND
// Эти пины заданы ATmega328P и библиотекой Wire.
#define LCD_SDA_PIN A4
#define LCD_SCL_PIN A5
