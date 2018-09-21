#ifndef FastLEDMethods_h
#define FastLEDMethods_h

void setupFastLED() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);         // for WS2812 (Neopixel)
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS); // for APA102 (Dotstar)
  FastLED.setDither(false);
  FastLED.setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(brightness);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTAGE, MILLI_AMPS);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

/****************************** Different tests ******************************/
/*****************************************************************************/

void strandTest() {
  static uint8_t i = 0;
  EVERY_N_SECONDS(1) {
    i++;
    if (i >= NUM_LEDS)
      i = 0;
  }
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  leds[i] = CRGB::Blue;
} // strandTest()

// Alternate rendering function just scrolls the current palette
// across the defined LED strip.
void palettetest( CRGB* ledarray, uint16_t numleds, const CRGBPalette16& gCurrentPalette) {
  static uint8_t startindex = 0;
  startindex--;
  fill_palette( ledarray, numleds, startindex, (256 / NUM_LEDS) + 1, gCurrentPalette, 255, currentBlending);
} // palettetest()

void changePalettePeriodically() {
  
  uint8_t secondHand = (millis() / 1000) % 60;
  static uint8_t lastSecond = 99;
  
  if(lastSecond != secondHand) {
    lastSecond = secondHand;
    CRGB p = CHSV(HUE_PURPLE, 255, 255);
    CRGB g = CHSV(HUE_GREEN, 255, 255);
    CRGB b = CRGB::Black;
    CRGB w = CRGB::White;
    if(secondHand ==  0)  { gTargetPalette = RainbowColors_p; }
    if(secondHand == 10)  { gTargetPalette = CRGBPalette16(g,g,b,b, p,p,b,b, g,g,b,b, p,p,b,b); }
    if(secondHand == 20)  { gTargetPalette = CRGBPalette16(b,b,b,w, b,b,b,w, b,b,b,w, b,b,b,w); }
    if(secondHand == 30)  { gTargetPalette = LavaColors_p; }
    if(secondHand == 40)  { gTargetPalette = CloudColors_p; }
    if(secondHand == 50)  { gTargetPalette = PartyColors_p; }
  }
  
} // changePalettePeriodically()








/********************************* Functions *********************************/
/*****************************************************************************/

void loadSettings() {
  brightness = EEPROM.read(0);

  gCurrentPatternIndex = EEPROM.read(1);
  if (gCurrentPatternIndex < 0)
    gCurrentPatternIndex = 0;
  else if (gCurrentPatternIndex >= patternCount)
    gCurrentPatternIndex = patternCount - 1;

  byte r = EEPROM.read(2);
  byte g = EEPROM.read(3);
  byte b = EEPROM.read(4);
  
  if((r + g + b) != 0) {
    solidColor = CRGB(r, g, b);
  }

  fastLEDPower = EEPROM.read(5);
  autoplay = EEPROM.read(6);
  autoplayDuration = EEPROM.read(7);

  gCurrentPaletteIndex = EEPROM.read(8);
  if (gCurrentPaletteIndex < 0)
    gCurrentPaletteIndex = 0;
  else if (gCurrentPaletteIndex >= paletteCount)
    gCurrentPaletteIndex = paletteCount - 1;
}

void setPower(uint8_t value) {
  fastLEDPower = value == 0 ? 0 : 1;

  EEPROM.write(5, fastLEDPower);
  EEPROM.commit();
}

void setAutoplay(uint8_t value)
  {
  autoplay = value == 0 ? 0 : 1;

  EEPROM.write(6, autoplay);
  EEPROM.commit();
}

void setAutoplayDuration(uint8_t value) {
  autoplayDuration = value;

  EEPROM.write(7, autoplayDuration);
  EEPROM.commit();

  autoPlayTimeout = millis() + (autoplayDuration * 1000);
}

void setPattern(uint8_t value) {
  if (value >= patternCount)
    value = patternCount - 1;

  gCurrentPatternIndex = value;

  if (autoplay == 0) {
    EEPROM.write(1, gCurrentPatternIndex);
    EEPROM.commit();
  }
}

void setPatternName(String name) {
  for(uint8_t i = 0; i < patternCount; i++) {
    if(patterns[i].name == name) {
      setPattern(i);
      break;
    }
  }
}

void setPalette(uint8_t value) {
  if (value >= paletteCount)
    value = paletteCount - 1;

  gCurrentPaletteIndex = value;

  EEPROM.write(8, gCurrentPaletteIndex);
  EEPROM.commit();
}

void setPaletteName(String name) {
  for(uint8_t i = 0; i < paletteCount; i++) {
    if(paletteNames[i] == name) {
      setPalette(i);
      break;
    }
  }
}

void setSolidColor(uint8_t r, uint8_t g, uint8_t b) {
  solidColor = CRGB(r, g, b);

  EEPROM.write(2, r);
  EEPROM.write(3, g);
  EEPROM.write(4, b);
  EEPROM.commit();

  setPattern(patternCount - 1);
}

void setSolidColor(CRGB color) {
  setSolidColor(color.r, color.g, color.b);
}

// increase or decrease the current pattern number, and wrap around at the ends
void adjustPattern(bool up) {
  if(up)
    gCurrentPatternIndex++;
  else
    gCurrentPatternIndex--;

  // wrap around at the ends
  if(gCurrentPatternIndex < 0)
    gCurrentPatternIndex = patternCount - 1;
  if(gCurrentPatternIndex >= patternCount)
    gCurrentPatternIndex = 0;

  if (autoplay == 0) {
    EEPROM.write(1, gCurrentPatternIndex);
    EEPROM.commit();
  }
}

void adjustBrightness(bool up) {
  if (up && brightnessIndex < brightnessCount - 1)
    brightnessIndex++;
  else if (!up && brightnessIndex > 0)
    brightnessIndex--;

  brightness = brightnessMap[brightnessIndex];

  FastLED.setBrightness(brightness);

  EEPROM.write(0, brightness);
  EEPROM.commit();
}

void setBrightness(uint8_t value) {
  if (value > 255)
    value = 255;
  else if (value < 0) value = 0;

  brightness = value;

  FastLED.setBrightness(brightness);

  EEPROM.write(0, brightness);
  EEPROM.commit();
}

// scale the brightness of all pixels down
void dimAll(byte value) {
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

void adjustPatternUpCallback() {
  adjustPattern(true);
  Trace("Pattern: ");
  Traceln(patterns[gCurrentPatternIndex].name);
}

void adjustPatternDownCallback() {
  adjustPattern(false);
  Trace("Pattern: ");
  Traceln(patterns[gCurrentPatternIndex].name);
}

void adjustSpeedUpCallback() {
  if(speed >= 255 - PRESS_ADJUST_SPEED) {
    speed = 255;
  } else {
    speed += PRESS_ADJUST_SPEED; 
  }
  Tracef("\rSpeed: %d        ", speed);
}

void adjustSpeedDownCallback() {
  if(speed < PRESS_ADJUST_SPEED) {
    speed = 0;
  } else {
    speed -= PRESS_ADJUST_SPEED; 
  }
  Tracef("\rSpeed: %d        ", speed);
}

void increaseSpeed() {
  static unsigned long lastChanged = 0;
  if(millis() - lastChanged > ADJUST_INTERVAL) {
    if(speed >= 255 - LONG_PRESS_ADJUST_SPEED) {
      speed = 255;
    } else {
      speed += LONG_PRESS_ADJUST_SPEED; 
    }
    lastChanged = millis();
    Tracef("\rSpeed: %d        ", speed);
  }
}

void decreaseSpeed() {
  static unsigned long lastChanged = 0;
  if(millis() - lastChanged > ADJUST_INTERVAL) {
    if(speed < LONG_PRESS_ADJUST_SPEED) {
      speed = 0;
    } else {
      speed -= LONG_PRESS_ADJUST_SPEED; 
    }
    lastChanged = millis();
    Tracef("\rSpeed: %d        ", speed);
  }
}

void adjustBrightnessUpCallback() {
  adjustBrightness(true);
  Tracef("\rBrigthness: %d        ", brightness);
}

void adjustBrightnessDownCallback() {
  adjustBrightness(false);
  Tracef("\rBrigthness: %d        ", brightness);
}

void increaseBrigthnessCallback() {
  static unsigned long lastChanged = 0;
  if(millis() - lastChanged > ADJUST_INTERVAL) {
    if(brightness >= 255 - LONG_PRESS_ADJUST_BRIGHTNESS) {
      brightness = 255;
    } else {
      brightness += LONG_PRESS_ADJUST_BRIGHTNESS; 
    }
    lastChanged = millis();
    FastLED.setBrightness(brightness);
    Tracef("\rBrigthness: %d        ", brightness);
  }

}

void decreaseBrigthnessCallback() {
  static unsigned long lastChanged = 0;
  if(millis() - lastChanged > ADJUST_INTERVAL) {
    if(brightness < LONG_PRESS_ADJUST_BRIGHTNESS) {
      brightness = 0;
    } else {
      brightness -= LONG_PRESS_ADJUST_BRIGHTNESS; 
    }
    lastChanged = millis();
    FastLED.setBrightness(brightness);
    Tracef("\rBrigthness: %d        ", brightness);
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

  if (autoplay && (millis() > autoPlayTimeout)) {
    adjustPattern(true);
    autoPlayTimeout = millis() + (autoplayDuration * 1000);
  }

  // Call the current pattern function once, updating the 'leds' array
  patterns[gCurrentPatternIndex].pattern();

  // insert a delay to keep the framerate modest
  // FastLED.delay(1000 / FRAMES_PER_SECOND);
  FastLED.show(); // Update and display the leds
}

#endif