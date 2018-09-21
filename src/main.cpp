
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

  // Some bug in ESP8266 requires this to be done.
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);

  #ifdef DEBUG
  chipInformation();
  #endif

  setupFastLED();
  setupButtons();

  EEPROM.begin(512);
  //TODO loadSettings();
  brightness = 200;
  FastLED.setBrightness(brightness); // After loading settings

  fastLEDPower = 1;
  autoplay = 0;
  Traceln("Setup complete!");
}

void loop() {
  // Run FastLED things

  handleButtons();
  
  fastLEDLoop();
}