#include <Arduino.h>
#include "dosing_controller.h"

#define WAIT_TIME_MS 1000UL
#define SLOW_FILL_TIME_MS 1000UL

DosingController::DosingController(
  Scale& scale,
  AugerMotor& auger,
  TargetMemory& targetMemory,
  FeedMemory& feedMemory
)
  : scale(scale),
    auger(auger),
    targetMemory(targetMemory),
    feedMemory(feedMemory),
    waitTimer(WAIT_TIME_MS),
    slowFillTimer(SLOW_FILL_TIME_MS) {
}

void DosingController::init() {
  feedMemory.init();
  auger.init();
}

void DosingController::start() {
  // loop() decides whether main feed is needed before it powers the auger.
  auger.setRunning(false);
  setState(State::MAIN_FILL);
}

void DosingController::stop() {
  auger.setRunning(false);
  setState(State::IDLE);
}

bool DosingController::isDosing() const {
  return state != State::IDLE;
}

void DosingController::loop() {
  const long targetWeight = (long)targetMemory.weight();
  const long currentWeight = scale.weightGrams();

  if (state != State::IDLE && currentWeight >= targetWeight) {
    stop();
    return;
  }

  switch (state) {
  case State::MAIN_FILL: {
    const long mainFillLimit = max(0L, targetWeight - (long)feedMemory.stopMarginGrams());

    if (currentWeight >= mainFillLimit) {
      auger.setRunning(false);
      setState(State::WAIT);
    }
    else {
      auger.setRunning(true);
    }
    break;
  }

  case State::WAIT:
    auger.setRunning(false);

    if (waitTimer.ready()) {
      auger.setRunning(true);
      setState(State::SLOW_FILL);
    }
    break;

  case State::SLOW_FILL:
    if (slowFillTimer.ready()) {
      auger.setRunning(false);
      setState(State::WAIT);
    }
    break;

  case State::IDLE:
    auger.setRunning(false);
    break;
  }
}

void DosingController::setState(State nextState) {
  state = nextState;

  if (nextState == State::WAIT) {
    waitTimer.reset();
  }
  else if (nextState == State::SLOW_FILL) {
    slowFillTimer.reset();
  }
}
