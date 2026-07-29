#pragma once

class AugerMotor {
public:
  void init();
  void setRunning(bool running);

private:
  bool running = false;
};
