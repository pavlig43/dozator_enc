#include <Arduino.h>
#include <EEPROM.h>
#include "feed_memory.h"

// Keep the old feed-setting addresses so a saved STOP WEIGHT value survives.
#define EEPROM_FEED_MARKER_ADDRESS 0
#define EEPROM_FEED_STOP_MARGIN_ADDRESS 9
#define EEPROM_FEED_MARKER 0xA6

#define DEFAULT_STOP_MARGIN_GRAMS 50
#define MIN_STOP_MARGIN_GRAMS 1
#define MAX_STOP_MARGIN_GRAMS 999

void FeedMemory::init() {
  if (initialized) {
    return;
  }

  initialized = true;

  if (EEPROM.read(EEPROM_FEED_MARKER_ADDRESS) != EEPROM_FEED_MARKER) {
    stopMarginValue = DEFAULT_STOP_MARGIN_GRAMS;
    return;
  }

  unsigned int savedStopMargin = DEFAULT_STOP_MARGIN_GRAMS;
  EEPROM.get(EEPROM_FEED_STOP_MARGIN_ADDRESS, savedStopMargin);
  stopMarginValue = constrain(savedStopMargin, MIN_STOP_MARGIN_GRAMS, MAX_STOP_MARGIN_GRAMS);
}

void FeedMemory::save() const {
  EEPROM.put(EEPROM_FEED_STOP_MARGIN_ADDRESS, stopMarginValue);
  EEPROM.update(EEPROM_FEED_MARKER_ADDRESS, EEPROM_FEED_MARKER);
}

unsigned int FeedMemory::stopMarginGrams() const {
  return stopMarginValue;
}

void FeedMemory::setStopMarginGrams(long grams) {
  stopMarginValue = constrain(grams, (long)MIN_STOP_MARGIN_GRAMS, (long)MAX_STOP_MARGIN_GRAMS);
}
