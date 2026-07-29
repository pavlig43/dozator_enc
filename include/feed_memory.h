#pragma once

#include <Arduino.h>

class FeedMemory {
public:
  void init();
  void save() const;
  unsigned int stopMarginGrams() const;
  void setStopMarginGrams(long grams);

private:
  unsigned int stopMarginValue = 50;
  bool initialized = false;
};
