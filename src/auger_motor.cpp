#include <Arduino.h>
#include "auger_motor.h"
#include "pin_destination.h"

#define AUGER_PWM 190

void AugerMotor::init() {
  pinMode(AUGER_IN1_PIN, OUTPUT);
  pinMode(AUGER_IN2_PWM_PIN, OUTPUT);

  // IN1 держим в LOW для выбора одного направления, а скорость задаём ШИМ на IN2.
  digitalWrite(AUGER_IN1_PIN, LOW);
  analogWrite(AUGER_IN2_PWM_PIN, 0);
  running = false;
}

void AugerMotor::setRunning(bool nextRunning) {
  if (running == nextRunning) {
    return;
  }

  running = nextRunning;
  analogWrite(AUGER_IN2_PWM_PIN, running ? AUGER_PWM : 0);
}
