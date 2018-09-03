#ifndef FastLEDMethods_h
#define FastLEDMethods_h

#include "FastLEDVariables.h"

void setupFastLED() {
  //FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);         // for WS2812 (Neopixel)
  FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS); // for APA102 (Dotstar)
  FastLED.setDither(false);
  FastLED.setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(brightness);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTAGE, MILLI_AMPS);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

// scale the brightness of all pixels down
void dimAll(byte value)
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(value);
  }
}

void reverseLeds() {
  CRGB temp;
  for(int i = 0; i < NUM_LEDS/2; i++ ) {
    temp = leds[(NUM_LEDS-1) - i];
    leds[(NUM_LEDS -1 )- i] = leds[i];
    leds[i] = temp; 
  }
}

void fastLEDLoop() {
  // Add entropy to random number generator; we use a lot of it.
  random16_add_entropy(random(65535));

  if (fastLEDPower == 0) {
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    // FastLED.delay(15);
    return;
  }

  // change to a new cpt-city gradient palette
  EVERY_N_SECONDS( secondsPerPalette ) {
    gCurrentPaletteIndex = addmod8( gCurrentPaletteIndex, 1, gGradientPaletteCount);
    gTargetPalette = gGradientPalettes[ gCurrentPaletteIndex ];
  }

  EVERY_N_MILLISECONDS(40) {
    // slowly blend the current palette to the next
    nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 8);
    gHue++;  // slowly cycle the "base color" through the rainbow
  }

  autoPlayTimeout = millis() + (autoplayDuration * 1000);

  // Call the current pattern function once, updating the 'leds' array
  patterns[gCurrentPatternIndex].pattern();


  // insert a delay to keep the framerate modest
  // FastLED.delay(1000 / FRAMES_PER_SECOND);
  FastLED.show(); // Update and display the leds
}

#endif FastLEDMethods_h