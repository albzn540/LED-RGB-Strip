#ifndef Button_h
#define Button_h

#include "Common.h"

void nextMode() {
  int8_t tmp = currentBtnMode + 1;
  // Change button mode and wrap around
  currentBtnMode = (ControlMode) ((tmp >= NUM_MODES) ? 0 : tmp);
}

void setupButtons() {
  btnOne.attachClick(nextMode);
  btnOne.attachLongPressStart(startSettingsMode);
}

void handleButtons() {

  // Update buttons
  btnOne.tick();
  btnTwo.tick();
  btnThree.tick();

  //Serial.printf("CurrentBtn mode: %d\n ", currentBtnMode);
  static ControlMode lastMode = currentBtnMode;

  if(currentBtnMode == Settings) {
    settingsMode();
  }

  if(currentBtnMode != lastMode) { // Only run switch statement once per press
    switch(currentBtnMode) {
      case AdjustBrightness:
        Traceln("Adjust brightness mode");
        btnTwo.attachClick(adjustBrightnessUpCallback);
        btnThree.attachClick(adjustBrightnessDownCallback);
        btnTwo.attachDuringLongPress(increaseBrigthnessCallback);
        btnThree.attachDuringLongPress(decreaseBrigthnessCallback);
        break;

      case AdjustPattern:
        Traceln("Adjust pattern mode");
        btnTwo.attachClick(adjustPatternUpCallback);
        btnThree.attachClick(adjustPatternDownCallback);
        break;

      case AdjustSpeed:
        Traceln("Adjust speed mode");
        btnTwo.attachClick(adjustSpeedUpCallback);
        btnThree.attachClick(adjustSpeedDownCallback);
        btnTwo.attachDuringLongPress(increaseSpeed);
        btnThree.attachDuringLongPress(decreaseSpeed);
        break;
    }
    startIndication(2000);
    indicateIndex(currentBtnMode, None);  //dynamically fix support for more buttonmodes
  }
  lastMode = currentBtnMode;
}

#endif