#ifndef Common_h
#define Common_h

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

// Use qsuba for smooth pixel colouring and qsubd for non-smooth pixel colouring
#define qsubd(x, b)  ((x>b)?b:0)                              // Digital unsigned subtraction macro. if result <0, then => 0. Otherwise, take on fixed value.
#define qsuba(x, b)  ((x>b)?x-b:0)                            // Analog Unsigned subtraction macro. if result <0, then => 0

#include <FastLED.h>
FASTLED_USING_NAMESPACE

extern "C" {
  #include "user_interface.h"
}

#include <Arduino.h>
#include <EEPROM.h>
#include <OneButton.h>
#include <TaskScheduler.h>
#include <ESP8266WiFi.h>

/*  Local libraries  */
#include "WiFi.h"
#include "DebugHelpers.h"

//--------------------------------- Settings ----------------------------------/
/*  Indication leds  */
#define   ESP_LED           D4

/*  FastLED Settings  */
#define DATA_PIN            D6
//#define CLK_PIN           D5            // Only needed for APA102
#define LED_TYPE            WS2812B       // WS2812B or APA102
#define COLOR_ORDER         GRB           // GRB        BGR
#define NUM_LEDS            30

#define VOLTAGE             5
#define MILLI_AMPS          3000    // IMPORTANT: set the max milli-Amps of your power supply (4A = 4000mA)
#define FRAMES_PER_SECOND   120     // here you can control the speed. With the Access Point / Web Server the animations run a bit slower.

CRGB leds[NUM_LEDS];

/*  Buttons   */
#define   BTN_ONE_PIN                   D3  // Change mode - Flash pin
#define   BTN_TWO_PIN                   D7  // Plus 
#define   BTN_THREE_PIN                 D2  // Minus
OneButton btnOne(BTN_ONE_PIN, true);
OneButton btnTwo(BTN_TWO_PIN, true);
OneButton btnThree(BTN_THREE_PIN, true);

/*  Task Manager  */
Scheduler taskManager;

//-------------------------------- Variables ---------------------------------//
/*  Button controls  */
enum ControlMode {
  AdjustBrightness,
  AdjustPattern,
  AdjustSpeed,
  None,
  Settings
};
#define NUM_MODES None // loopable control modes
ControlMode currentBtnMode = AdjustBrightness;

/*  Define adjusting speeds  */
#define ADJUST_INTERVAL                 200 //ms
#define PRESS_ADJUST_SPEED              20  
#define LONG_PRESS_ADJUST_SPEED         5
#define LONG_PRESS_ADJUST_BRIGHTNESS    5
// brightness adjusting steps are set in FastLEDVariables.h

/*  More local libraries  */
#include "OTA.h"
#include "FastLEDVariables.h"   // FastLed variables
#include "FastLEDMethods.h"     // FastLed functions
#include "IndicationLeds.h"     // Indication leds functions
#include "Settings.h"
#include "Button.h"             // Button functions
#endif