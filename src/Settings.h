#ifndef Settings_h
#define Settings_h

/*  Local libraries  */
#include "Common.h"
#include "WiFi.h"
#include "OTA.h"

unsigned long startSettingsMs = 0;
#define SETTINGS_DURATION     8000 //ms

typedef struct {
  callbackFunction function;
  const char* name;
} SettingsFunction;
typedef SettingsFunction SettingsFunctions[];

SettingsFunctions settingsFunctions = {
  toggleAP,           "Toggle AP",
  toggleStationMode,  "Toggle station mode",
  startOTA,           "Start OTA"
};

const int8_t settingsCount = ARRAY_SIZE(settingsFunctions);
int8_t settingsIndex = 0;

void exitSettingsMode() {
  currentBtnMode = AdjustBrightness;
  Serial.printf("Choosing setting: %s\n", settingsFunctions[settingsIndex].name);
  settingsFunctions[settingsIndex].function();
}

void settingsMode() {
  if(millis() - startSettingsMs > SETTINGS_DURATION) {
    // Settings timeout - going back to regular modes
    exitSettingsMode();
  } else {
    writeIndicationLeds(settingsCount);
  }
}

void nextSetting() {
  // Next setting and wrap around
  settingsIndex = (settingsIndex + 1 >= settingsCount) ? 0 : settingsIndex + 1;
  Serial.printf("Setting: %s\n", settingsFunctions[settingsIndex].name);
  indicateIndex(settingsIndex);
}

void prevSetting() {
  // Previous setting and wrap around
  // Note the '- 1' on the end of the line
  settingsIndex = ((settingsIndex - 1 < 0) ? settingsCount : settingsIndex) - 1;
  Serial.printf("Setting: %s\n", settingsFunctions[settingsIndex].name);
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