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

void startIndication(unsigned long durationMs = PRESET_INDICATION_DURATION) {
  indicationDuration = durationMs;  // set indication duration
  tWriteIndicationLeds.enable();    // start indication task
}

void setIndicationDuration(unsigned long ms) {
  indicationDuration = ms;
}

void setNumberOfIndicationLeds(uint8_t num) {
  numberOfIndicationLeds = num;
}

void writeIndicationLeds(uint8_t length) {
  for(uint8_t i = 0; i < length; i++) {
    leds[i] = indicationLeds[i];
  }
}

void writeIndicationLeds() {
  writeIndicationLeds(numberOfIndicationLeds);
}

void writeIndicationLedsCallback() {
  if(millis() - startIndicationMs < indicationDuration) {
    writeIndicationLeds();
  } else {
    tWriteIndicationLeds.disable();
  }
}

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