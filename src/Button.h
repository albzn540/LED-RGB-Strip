#ifndef Button_h
#define Button_h

#include "Common.h"

void handleButtons() {

  // Update buttons
  btnOne.tick();

  //Serial.printf("CurrentBtn mode: %d\n ", currentBtnMode);
  static ControlMode lastMode = None;

}

#endif