
#include <FastLED.h>
FASTLED_USING_NAMESPACE

extern "C" {
  #include "user_interface.h"
}

#include <Arduino.h>
#include <EEPROM.h>

/* Local files */
#include "Common.h"
#include "DebugHelpers.h"

#define DEBUG true  // Change this to enable/disable debugging

// ---------------------------- Settings ----------------------------//
/*  Indication leds  */
#define   ESP_LED           D4

/*  FastLED Settings  */
#define DATA_PIN            D7
#define CLK_PIN             D5
#define LED_TYPE            APA102        // WS2812B or APA102
#define COLOR_ORDER         BGR           // GRB        BGR
#define NUM_LEDS            60

#define VOLTAGE             5
#define MILLI_AMPS          3000     // IMPORTANT: set the max milli-Amps of your power supply (4A = 4000mA)
#define FRAMES_PER_SECOND   120      // here you can control the speed. With the Access Point / Web Server the animations run a bit slower.

CRGB leds[NUM_LEDS];

#include "FastLEDVariables.h"
#include "FastLEDMethods.h"

/*  Button controls  */
enum ControlMode {
    First
};
ControlMode currentBtnMode = First;


void setup() {
  beginDebug();
  Traceln("Initializing RGB Led lights...");
  Serial.setDebugOutput(false); // Extra debug stuff

  setupFastLED();

  EEPROM.begin(512);
  //TODO loadSettings();
  FastLED.setBrightness(brightness); // After loading settings

  Traceln("Setup complete!");
}

void loop() {
  // Run FastLED things
  fastLEDLoop();
}