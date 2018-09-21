#ifndef IndicationLeds_h
#define IndicationLeds_h

/*  Local libraries  */
#include "Common.h"

#define NUM_INDICATION_LEDS   4
CRGB indicationLeds[NUM_INDICATION_LEDS] = { CRGB::DimGrey };
uint8_t numberOfIndicationLeds = NUM_INDICATION_LEDS; // Number of leds to display

#define PRESET_INDICATION_DURATION 1500
unsigned long indicationDuration = 1500; //ms 
unsigned long startIndicationMs  = 0;

void writeIndicationLedsCallback();   // Declare functions that are necessary
bool resetIndicationTimer();          // for the task
void resetIndicationLeds();
Task tWriteIndicationLeds(0, TASK_FOREVER, writeIndicationLedsCallback, &taskManager, false, resetIndicationTimer, resetIndicationLeds);

bool resetIndicationTimer() {
  startIndicationMs = millis();
  return true;
}

void resetIndicationLeds() {
  numberOfIndicationLeds = NUM_INDICATION_LEDS;
}

/** Starts indication */
void startIndication(unsigned long durationMs = PRESET_INDICATION_DURATION) {
  indicationDuration = durationMs;  // set indication duration
  tWriteIndicationLeds.enable();    // start indication task
}

/** Sets the indication duration (for one run) */
void setIndicationDuration(unsigned long ms) {
  indicationDuration = ms;
}

/** Sets the number of leds to be written to the leds array */
void setNumberOfIndicationLeds(uint8_t num) {
  numberOfIndicationLeds = num;
}

void writeIndicationLeds(uint8_t length) {
  for(uint8_t i = 0; i < length; i++) {
    leds[i] = indicationLeds[i];
  }
}

/** Write the indication leds data to fastLED for display */
void writeIndicationLeds() {
  writeIndicationLeds(numberOfIndicationLeds);
}

/** Callback function used by the task handling writing to fastLED */
void writeIndicationLedsCallback() {
  if(millis() - startIndicationMs < indicationDuration) {
    writeIndicationLeds();
  } else {
    tWriteIndicationLeds.disable();
  }
}

/** Writes a color to the first led */
void indicateColor(CRGB color) {
  startIndication();
  numberOfIndicationLeds = 1;
  indicationLeds[0] = color;
}

/** Indicates an index by illumination that led x
 *  steps from the start of the strip */
void indicateIndex(uint8_t index, CRGB indicateColor, CRGB bgColor = CRGB::Gray, uint8_t length = NUM_INDICATION_LEDS) {
  setNumberOfIndicationLeds(length);
  for(int i = 0; i < length; i++) {
    indicationLeds[i] = bgColor;
  }
  indicationLeds[index] = indicateColor;
  Tracef("Indicate index: %d\n", index);
}

void indicateIndex(uint8_t index, uint8_t length = NUM_INDICATION_LEDS) {
  indicateIndex(index, CRGB::DeepPink, CRGB::Gray, length);
}

#endif