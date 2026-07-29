#include <Arduino.h>
#include "auger_motor.h"

#define AUGER_PIN 11
#define AUGER_PWM 190

void AugerMotor::init() {
  pinMode(AUGER_PIN, OUTPUT);
  analogWrite(AUGER_PIN, 0);
  running = false;
}

void AugerMotor::setRunning(bool nextRunning) {
  if (running == nextRunning) {
    return;
  }

  running = nextRunning;
  analogWrite(AUGER_PIN, running ? AUGER_PWM : 0);
}
