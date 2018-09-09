void showSolidColor() {
  fill_solid(leds, NUM_LEDS, solidColor);
}

// Patterns from FastLED example DemoReel100: https://github.com/FastLED/FastLED/blob/master/examples/DemoReel100/DemoReel100.ino

void rainbow() {
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 255 / NUM_LEDS);
}

void rainbowWithGlitter() {
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void rainbowSolid() {
  fill_solid(leds, NUM_LEDS, CHSV(gHue, 255, 255));
}

void confetti() {
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  // leds[pos] += CHSV( gHue + random8(64), 200, 255);
  leds[pos] += ColorFromPalette(palettes[gCurrentPaletteIndex], gHue + random8(64));
}

void sinelon() {
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16(speed, 0, NUM_LEDS);
  static int prevpos = 0;
  CRGB color = ColorFromPalette(palettes[gCurrentPaletteIndex], gHue, 255);
  if( pos < prevpos ) {
    fill_solid( leds+pos, (prevpos-pos)+1, color);
  } else {
    fill_solid( leds+prevpos, (pos-prevpos)+1, color);
  }
  prevpos = pos;
}

void bpm() {
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t beat = beatsin8( speed, 64, 255);
  CRGBPalette16 palette = palettes[gCurrentPaletteIndex];
  for ( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
  }
}

void juggle() {
  static uint8_t    numdots =   4; // Number of dots in use.
  static uint8_t   faderate =   2; // How long should the trails be. Very low value = longer trails.
  static uint8_t     hueinc =  255 / numdots - 1; // Incremental change in hue between each dot.
  static uint8_t    thishue =   0; // Starting hue.
  static uint8_t     curhue =   0; // The current hue
  static uint8_t    thissat = 255; // Saturation of the colour.
  static uint8_t thisbright = 255; // How bright should the LED/display be.
  static uint8_t   basebeat =   5; // Higher = faster movement.

  static uint8_t lastSecond =  99;  // Static variable, means it's only defined once. This is our 'debounce' variable.
  uint8_t secondHand = (millis() / 1000) % 30; // IMPORTANT!!! Change '30' to a different value to change duration of the loop.

  if (lastSecond != secondHand) { // Debounce to make sure we're not repeating an assignment.
    lastSecond = secondHand;
    switch (secondHand) {
      case  0: numdots = 1; basebeat = 20; hueinc = 16; faderate = 2; thishue = 0; break; // You can change values here, one at a time , or altogether.
      case 10: numdots = 4; basebeat = 10; hueinc = 16; faderate = 8; thishue = 128; break;
      case 20: numdots = 8; basebeat =  3; hueinc =  0; faderate = 8; thishue = random8(); break; // Only gets called once, and not continuously for the next several seconds. Therefore, no rainbows.
      case 30: break;
    }
  }

  // Several colored dots, weaving in and out of sync with each other
  curhue = thishue; // Reset the hue values.
  fadeToBlackBy(leds, NUM_LEDS, faderate);
  for ( int i = 0; i < numdots; i++) {
    //beat16 is a FastLED 3.1 function
    leds[beatsin16(basebeat + i + numdots, 0, NUM_LEDS)] += CHSV(gHue + curhue, thissat, thisbright);
    curhue += hueinc;
  }
}

void fire() {
  heatMap(HeatColors_p, false);
}

void water() {
  heatMap(IceColors_p, false);
}

// ColorWavesWithPalettes by Mark Kriegsman: https://gist.github.com/kriegsman/8281905786e8b2632aeb
// This function draws color waves with an ever-changing,
// widely-varying set of parameters, using a color palette.
void colorwaves( CRGB* ledarray, uint16_t numleds, CRGBPalette16& palette) {
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;

  // uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 300, 1500);

  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5, 9);
  uint16_t brightnesstheta16 = sPseudotime;

  for ( uint16_t i = 0 ; i < numleds; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;
    uint16_t h16_128 = hue16 >> 7;
    if ( h16_128 & 0x100) {
      hue8 = 255 - (h16_128 >> 1);
    } else {
      hue8 = h16_128 >> 1;
    }

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);

    uint8_t index = hue8;
    //index = triwave8( index);
    index = scale8( index, 240);

    CRGB newcolor = ColorFromPalette( palette, index, bri8);

    uint16_t pixelnumber = i;
    pixelnumber = (numleds - 1) - pixelnumber;

    nblend( ledarray[pixelnumber], newcolor, 128);
  }
} // colorwaves()
void colorWaves() {
  colorwaves(leds, NUM_LEDS, gCurrentPalette);
}

void beatwave() {
  uint8_t wave1 = beatsin8(9, 0, 255);    // That's the same as beatsin8(9);
  uint8_t wave2 = beatsin8(8, 0, 255);
  uint8_t wave3 = beatsin8(7, 0, 255);
  uint8_t wave4 = beatsin8(6, 0, 255);

  for (int i=0; i<NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(gCurrentPalette, i+wave1+wave2+wave3+wave4, 255, currentBlending); 
  }

} // beatwave()

void blendwave() {
  uint8_t speed_blendwave = beatsin8(6,0,255);
  CRGB clr1 = blend(CHSV(beatsin8(3,0,255),255,255),
    CHSV(beatsin8(4,0,255),255,255), speed_blendwave);
  CRGB clr2 = blend(CHSV(beatsin8(4,0,255),255,255),
    CHSV(beatsin8(3,0,255),255,255), speed_blendwave);
  uint8_t loc1 = beatsin8(10,0,NUM_LEDS-1);
  fill_gradient_RGB(leds, 0, clr2, loc1, clr1);
  fill_gradient_RGB(leds, loc1, clr2, NUM_LEDS-1, clr1);
} // blendwave()

void ripple() {
  #define maxsteps 16               // Case statement wouldn't allow a variable.
  static int center = 0;            // Center of the current ripple.
  static int step = -1;             // -1 is the initializing step.
  static uint8_t colour;            // Ripple colour is randomized.
  static uint8_t myfade = 255;      // Starting brightness.
  static uint8_t fadeval = 128;
  fadeToBlackBy(leds, NUM_LEDS, fadeval);   // 8 bit, 1 = slow, 255 = fast
  
  switch (step) {
    case -1:                                // Initialize ripple variables.
      center = random(NUM_LEDS);
      colour = random8();
      step = 0;
      break;
    case 0:
      leds[center] = ColorFromPalette(gCurrentPalette,
        colour, myfade, currentBlending);
      step ++;
      break;
    case maxsteps: // At the end of the ripples.
      step = -1;
      break;
    default: // Middle of the ripples.
      leds[(center + step + NUM_LEDS) % NUM_LEDS] += ColorFromPalette(
          gCurrentPalette, colour, myfade/step*2, currentBlending);
          // Simple wrap from Marc Miller
      leds[(center - step + NUM_LEDS) % NUM_LEDS] += ColorFromPalette(
          gCurrentPalette, colour, myfade/step*2, currentBlending);
      step ++; // Next step.
      break;  
  } // switch step
} // ripple()

void plasma() {// This is the heart of this program. Sure is short. . . and fast.
  // Setting phase change for a couple of waves.
  int thisPhase = beatsin8(6,-64,64); 
  int thatPhase = beatsin8(7,-64,64);

  /* For each of the LED's in the strand, set a brightness based
  on a wave as follows: */
  for (int k=0; k<NUM_LEDS; k++) {
    int colorIndex = cubicwave8((k*23)+thisPhase)/2 + cos8((k*15)+thatPhase)/2;
    /* Create a wave and add a phase change and add another wave with its own
    phase change.. Hey, you can even change the frequencies if you wish. */

    int thisBright = qsuba(colorIndex, beatsin8(7,0,96));
    /* qsub gives it a bit of 'black' dead space by setting sets a minimum
    value. If colorIndex < current value of beatsin8(), then bright = 0.
    Otherwise, bright = colorIndex.. */

    leds[k] = ColorFromPalette(gCurrentPalette, 
      colorIndex, thisBright, currentBlending);
    // Let's now add the foreground colour.
  }
} // plasma()

void serendipitous() {

  static uint16_t Xorig = 0x012;
  static uint16_t Yorig = 0x015;
  static uint16_t X;
  static uint16_t Y;
  static uint16_t Xn;
  static uint16_t Yn;
  static uint8_t index;

  EVERY_N_SECONDS(5) {
    uint8_t baseC = random8();
    gTargetPalette = CRGBPalette16(CHSV(baseC-3, 255, random8(192,255)), CHSV(baseC+2, 255, random8(192,255)), CHSV(baseC+5, 192, random8(192,255)), CHSV(random8(), 255, random8(192,255)));

    X = Xorig;
    Y = Yorig;    
  }

//  Xn = X-(Y/2); Yn = Y+(Xn/2);
//  Xn = X-Y/2;   Yn = Y+Xn/2;
//  Xn = X-(Y/2); Yn = Y+(X/2.1);
  Xn = X-(Y/3); Yn = Y+(X/1.5);
//  Xn = X-(2*Y); Yn = Y+(X/1.1);
  
  X = Xn;
  Y = Yn;

  index=(sin8(X)+cos8(Y))/2;  // Guarantees maximum value of 255

  CRGB newcolor = ColorFromPalette(gCurrentPalette, index, 255, currentBlending);
  
//  nblend(leds[X%NUM_LEDS-1], newcolor, 224);          // Try and smooth it out a bit. Higher # means less smoothing.
  nblend(leds[map(X,0,65535,0,NUM_LEDS)], newcolor, 224); // Try and smooth it out a bit. Higher # means less smoothing.
  
  fadeToBlackBy(leds, NUM_LEDS, 16);                    // 8 bit, 1 = slow, 255 = fast

} // serendipitous()

void rainbow_beat() {
  uint8_t beatA = beatsin8(17, 0, 255); // Starting hue
  uint8_t beatB = beatsin8(13, 0, 255);
  fill_rainbow(leds, NUM_LEDS, (beatA+beatB)/2, 8);
  // Use FastLED's fill_rainbow routine.
} // rainbow_beat()
