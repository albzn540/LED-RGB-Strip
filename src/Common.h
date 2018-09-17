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

#include "DebugHelpers.h"

//--------------------------------- Settings ----------------------------------/
/*  Indication leds  */
#define   ESP_LED           D4

/*  FastLED Settings  */
#define DATA_PIN            D6
//#define CLK_PIN             D5          // Only needed for APA102
#define LED_TYPE            WS2812B       // WS2812B or APA102
#define COLOR_ORDER         GRB           // GRB        BGR
#define NUM_LEDS            25

#define VOLTAGE             5
#define MILLI_AMPS          3000    // IMPORTANT: set the max milli-Amps of your power supply (4A = 4000mA)
#define FRAMES_PER_SECOND   120     // here you can control the speed. With the Access Point / Web Server the animations run a bit slower.

CRGB leds[NUM_LEDS];
#include "FastLEDVariables.h"
#include "FastLEDMethods.h"

/*  Buttons   */
#define   BTN_ONE_PIN                   D3      // Flash pin
OneButton btnOne(BTN_ONE_PIN, true);



//-------------------------------- Variables ---------------------------------//
/*  Button controls  */
enum ControlMode {
    First
};
ControlMode currentBtnMode = First;

#include "Button.h" // Button functions
#endif