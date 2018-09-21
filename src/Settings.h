#ifndef Settings_h
#define Settings_h

/*  Local libraries  */
#include "Common.h"
#include "WiFi.h"
#include "OTA.h"

unsigned long startSettings = 0;
#define SETTINGS_DURATION     8000 //ms

typedef struct {
  callbackFunction function;
  String name;
} SettingsFunction;
typedef SettingsFunction SettingsFunctions[];

SettingsFunctions settingsFunctions = {
  toggleAP,           "Toggle AP",
  toggleStationMode,  "Toggle station mode",
  startOTA,           "Start OTA"
};

const uint8_t settingsCount = ARRAY_SIZE(settingsFunctions);
uint8_t settingsIndex = 0;

void exitSettingsMode() {
  currentBtnMode = AdjustBrightness;
}

void settingsMode() {
  if(millis() - startSettings > SETTINGS_DURATION) {
    // Settings timeout - going back to regular modes
    exitSettingsMode();
  } else {
    writeIndicationLeds(settingsCount);
  }
}

void nextSetting() {
  // Next setting and wrap around
  settingsIndex = (settingsIndex + 1 >= settingsCount) ? 0 : settingsIndex + 1;
  indicateIndex(settingsIndex);
}

void prevSetting() {
  // Previous setting and wrap around
  // Note the '- 1' on the end of the line
  settingsIndex = ((settingsIndex - 1 < 0) ? settingsCount : settingsIndex) - 1;
  indicateIndex(settingsIndex);
}

void startSettingsMode() {
  currentBtnMode = Settings;
  Traceln("Settings-mode, waiting for input");
  btnOne.attachClick(exitSettingsMode);
  btnTwo.attachClick(nextSetting);
  btnThree.attachClick(prevSetting);
}

#endif