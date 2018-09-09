#ifndef FastLEDVariables_h
#define FastLEDVariables_h

#include <FastLED.h>
FASTLED_USING_NAMESPACE

uint8_t fastLEDPower = 1;
uint8_t brightness = 0;
uint8_t speed = 30;

CRGB solidColor = CRGB::Blue;

/*  Predefined brightness (Button clicks will loop through these)   */
const uint8_t brightnessCount = 5;
uint8_t brightnessMap[brightnessCount] = { 16, 32, 64, 128, 255 };
uint8_t brightnessIndex = 0;

uint8_t autoplay = 0;
uint8_t autoplayDuration = 10;
unsigned long autoPlayTimeout = 0;

// Necessary for some shit
TBlendType currentBlending = LINEARBLEND; //set blending type


/* Variable setup for effect helpers */
// For lineit (Sending pixels up/down the strip)
bool thisdir = 0;

// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 50, suggested range 20-100
uint8_t cooling = 49;

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
uint8_t sparking = 60;


/********************************** Palettes **********************************/
/******************************************************************************/
#include "GradientPalettes.h"
// Forward declarations of an array of cpt-city gradient palettes, and
// a count of how many there are.  The actual color palette definitions
// are at the bottom of this file.
extern const TProgmemRGBGradientPalettePtr gGradientPalettes[];

CRGBPalette16 gCurrentPalette( CRGB::Black); // Current palette
uint8_t gCurrentPaletteIndex = 0;           // Index of current palette

CRGBPalette16 gTargetPalette( gGradientPalettes[0] );

// ten seconds per color palette makes a good demo
// 20-120 is better for deployment
uint8_t secondsPerPalette = 10;

/****** Own Palettes ******/
CRGBPalette16 IceColors_p = CRGBPalette16(
  CRGB::Black,
  CRGB::Blue,
  CRGB::Aqua,
  CRGB::White
);
typedef struct {
  CRGBPalette16 palette;
  String name;
 } PaletteAndName;
typedef PaletteAndName PaletteAndNameList[];

const CRGBPalette16 palettes[] = {
  RainbowColors_p,
  RainbowStripeColors_p,
  CloudColors_p,
  LavaColors_p,
  OceanColors_p,
  ForestColors_p,
  PartyColors_p,
  HeatColors_p,
  IceColors_p
};

const uint8_t paletteCount = ARRAY_SIZE(palettes);

const String paletteNames[paletteCount] = {
  "Rainbow",
  "Rainbow Stripe",
  "Cloud",
  "Lava",
  "Ocean",
  "Forest",
  "Party",
  "Heat",
  "Ice"
 };







/************************************ Hue ************************************/
/*****************************************************************************/
uint8_t gHue = 0; // rotating "base color" used by many of the patterns






/********************************** Patterns **********************************/
/******************************************************************************/
typedef void (*Pattern)();
typedef Pattern PatternList[];
typedef struct {
  Pattern pattern;
  String name;
} PatternAndName;
typedef PatternAndName PatternAndNameList[];

#include "effects/EffectHelpers.h"
#include "effects/Pride.h"
#include "effects/Twinkles.h"
#include "effects/TwinkleFOX.h"
#include "effects/FastLEDEffects.h"

// List of patterns to cycle through.  Each is defined as a separate function below.
PatternAndNameList patterns = {
  // Pride
  { pride,                  "Pride" },

  //FastLedEffects
  // { showSolidColor,         "Solid Color" } <-- is declaired last
  { rainbow,                "Rainbow" },
  { rainbowWithGlitter,     "Rainbow With Glitter" },
  { rainbowSolid,           "Solid Rainbow" },
  { confetti,               "Confetti" },
  { sinelon,                "Sinelon" },
  { bpm,                    "Beat" },
  { juggle,                 "Juggle" },
  { fire,                   "Fire" },
  { water,                  "Water" },
  { colorWaves,             "Colorwaves" },
  { beatwave,               "Beatwave" },
  { blendwave,              "Blendwave" },
  { ripple,                 "Ripple" },
  { plasma,                 "Plasma" },
  { serendipitous,          "Serendipitous" },
  { rainbow_beat,           "Rainbow_beat" },

  // Twinkle patterns
  { rainbowTwinkles,        "Rainbow Twinkles" },
  { snowTwinkles,           "Snow Twinkles" },
  { cloudTwinkles,          "Cloud Twinkles" },
  { incandescentTwinkles,   "Incandescent Twinkles" },

  // TwinkleFOX patterns
  { retroC9Twinkles,        "Retro C9 Twinkles" },
  { redWhiteTwinkles,       "Red & White Twinkles" },
  { blueWhiteTwinkles,      "Blue & White Twinkles" },
  { redGreenWhiteTwinkles,  "Red, Green & White Twinkles" },
  { fairyLightTwinkles,     "Fairy Light Twinkles" },
  { snow2Twinkles,          "Snow 2 Twinkles" },
  { hollyTwinkles,          "Holly Twinkles" },
  { iceTwinkles,            "Ice Twinkles" },
  { partyTwinkles,          "Party Twinkles" },
  { forestTwinkles,         "Forest Twinkles" },
  { lavaTwinkles,           "Lava Twinkles" },
  { fireTwinkles,           "Fire Twinkles" },
  { cloud2Twinkles,         "Cloud 2 Twinkles" },
  { oceanTwinkles,          "Ocean Twinkles" },

  { showSolidColor,         "Solid Color" }
};

const uint8_t patternCount = ARRAY_SIZE(patterns);
uint8_t gCurrentPatternIndex = 0; // Index number of which pattern is current

#endif