
/*
    ___        _______ ____   ___  __  __ _____ 
   / \ \      / | ____/ ___| / _ \|  \/  | ____|
  / _ \ \ /\ / /|  _| \___ \| | | | |\/| |  _|  
 / ___ \ V  V / | |___ ___) | |_| | |  | | |___ 
/_/   \_\_/\_/  |_____|____/ \___/|_|  |_|_____|
 _     _____ ____  ____                         
| |   | ____|  _ \/ ___|                        
| |   |  _| | | | \___ \                        
| |___| |___| |_| |___) |                       
|_____|_____|____/|____/                        

An awesome LED sketch written by Albin Winkelmann
*/

#define DEBUG true  // Change this to enable/disable debugging
#define SUPERDEBUG false

/* Local files */
#include "Common.h" // <-- All settings in here

void setup() {
  beginDebug();
  Traceln("\n\nInitializing RGB Led lights...");
  delay(100);
  Serial.setDebugOutput(SUPERDEBUG); // Extra debug stuff

  setupFastLED();

  EEPROM.begin(512);
  //TODO loadSettings();
  brightness = 200;
  FastLED.setBrightness(brightness); // After loading settings

  fastLEDPower = 1;
  autoplay = 1;
  Traceln("Setup complete!");
}

void loop() {
  // Run FastLED things
  static int lastPattern = gCurrentPatternIndex;
  int currentPattern = gCurrentPatternIndex;
  
  if(lastPattern != currentPattern) {
    Serial.printf("Pattern: %s\n", patterns[gCurrentPatternIndex].name.c_str());
  }
  lastPattern = currentPattern;
  fastLEDLoop();
}