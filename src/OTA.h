#ifndef OTA_h
#define OTA_h

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <FS.h>
#include <ArduinoOTA.h>

/*  Local libraries  */
#include "Common.h"
#include "WiFi.h"
#include "DebugHelpers.h"

/*  OTA  */
bool OTAOn = true;

void ledPercent(uint8_t progress, uint8_t total) {
  uint8_t x = map(progress, 0, total, 0, NUM_LEDS);
  for(uint8_t i = 0; i <= x; i++) {
    leds[i] = CRGB::Blue;
  }
}

void startOTA() {

  Trace("Wifimode: "); Traceln(wifiMode);
  
  //start wifi if it's off
  if(wifiMode != STAT_MODE) {
    if(wifiMode == AP_MODE)
      turnOffWifiAp(); // turn of AP if it's currently on
    startWiFiStation();
  }

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    SPIFFS.end();
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    for(uint8_t i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Green;
    }
    FastLED.show();
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    int percentage = (progress / (total / 100));
    Serial.printf("Progress: %u%%\r", percentage);
    ledPercent(percentage, 100);
    FastLED.show();
  });
  ArduinoOTA.onError([](ota_error_t error) {
    for(uint8_t i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Red;
    }
    FastLED.show();
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  OTAOn = true;

  Serial.println("OTA Ready.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


#endif