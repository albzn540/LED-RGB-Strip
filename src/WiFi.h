#ifndef WiFiSettings_h
#define WiFiSettings_h

#include <ESP8266WiFi.h>
#include "Common.h"
#include "DebugHelpers.h"

// Wi-Fi network to connect to (if not in AP mode)
char ssid[] = "";
char password[] = "";

/* Access-Point settings*/
#define AP_SSID             ""
#define AP_PASSWORD         ""

#define DEBUG_WIFI 1

typedef enum {
  OFF,
  AP_MODE,
  STAT_MODE
} Wifimodes;
Wifimodes wifiMode = OFF;

void startAp() {
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  wifiMode = AP_MODE;

  WiFi.softAP(AP_SSID, AP_PASSWORD);

  Serial.printf("Connect to Wi-Fi access point: %s\n", AP_SSID);
  Serial.println("and open http://192.168.4.1 in your browser");
}

void turnOffWifiAp() {
  Serial.print("Turning off AP...");
  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_OFF);
  wifiMode = OFF;
  Serial.println("\tTurned off!");
}

void turnOffWifiStat() {
  Serial.print("Turning off wifi station mode... ");
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  wifiMode = OFF;
  Serial.println("\tTurned off!");
}

void turnOffWifi() {
  turnOffWifiAp();
  turnOffWifiStat();
}

void startWiFiStation() {
  WiFi.disconnect();
  delay(100);
  WiFi.mode(WIFI_STA);
  wifiMode = STAT_MODE;
  Serial.printf("Connecting to %s\n", ssid);
  if (String(WiFi.SSID()) != String(ssid)) {
    WiFi.begin(ssid, password);
    Traceln("Wifi.begin called");
  }

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.print("Connected! Open http://");
  Serial.print(WiFi.localIP());
  Serial.println(" in your browser");
}

void setupWiFi(Wifimodes mode) {
  if(mode == AP_MODE) startAp();
  else startWiFiStation();
}

void toggleStationMode() {
  if(wifiMode == STAT_MODE) {
    turnOffWifiStat();
  } else {
    startWiFiStation();
  }
  Traceln("Toggle StationMode called");
}

void toggleAP() {
  if(WiFi.getMode() == 0) {
    startAp();
  } else {
    turnOffWifiAp();
  }
  Traceln("Toggle AP called");
}


void handleWifi() {
  static uint16_t lastStatus = 0;

  if(lastStatus != WiFi.status()) {
    Tracef2("\nNew Wifi status: %d\n", WiFi.status());
    lastStatus = WiFi.status();
  }
}

#endif