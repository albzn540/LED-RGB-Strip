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

void writeIndicationLeds();   // Declare functions that are necessary
bool resetIndicationLeds();  // for the task
Task tWriteIndicationLeds(0, TASK_FOREVER, writeIndicationLeds, &taskManager, resetIndicationLeds);

bool resetIndicationLeds() {
  startIndicationMs = millis();
  numberOfIndicationLeds = NUM_INDICATION_LEDS;
  return true;
}

void startIndication(unsigned long durationMs = PRESET_INDICATION_DURATION) {
  indicationDuration = durationMs;
  tWriteIndicationLeds.enable();
}

void setIndicationDuration(uint8_t ms) {
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
  if(millis() - startIndicationMs > indicationDuration) {
    writeIndicationLeds();
  } else {
    tWriteIndicationLeds.disable();
  }
}

void indicateIndex(uint8_t index, CRGB indicateColor, CRGB bgColor = CRGB::Black, uint8_t length = NUM_INDICATION_LEDS) {
  setNumberOfIndicationLeds(length);
  for(int i = 0; i < length; i++) {
    indicationLeds[i] = bgColor;
  }
  indicationLeds[index] = indicateColor;
  Tracef2("Indicate index: %d\n", index);
}

void indicateIndex(uint8_t index, uint8_t length = NUM_INDICATION_LEDS) {
  indicateIndex(index, CRGB::DeepPink, CRGB::Black, length);
}

#endif