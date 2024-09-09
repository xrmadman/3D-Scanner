#ifndef WIFIHANDLING_H
#define WIFIHANDLING_H

#include <WiFi.h>
#include <Preferences.h>

Preferences preferences;

const char* defaultSSID = "ESP32_AP";
const char* defaultPassword = "12345678";
int maxConnectionAttempts = 5;

void initWiFi() {
  String ssid = preferences.getString("ssid", "");
  String password = preferences.getString("password", "");

  if (ssid.length() > 0) {
    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.println("Connecting to WiFi...");

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
      if (++attempts >= maxConnectionAttempts) {
        Serial.println("\nFailed to connect, switching to AP mode.");
        WiFi.softAP(defaultSSID, defaultPassword);
        Serial.print("ESP32 AP IP Address: ");
        Serial.println(WiFi.softAPIP());
        return;
      }
    }

    Serial.println("\nConnected to WiFi.");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("No stored WiFi credentials, starting AP mode.");
    WiFi.softAP(defaultSSID, defaultPassword);
    Serial.print("ESP32 AP IP Address: ");
    Serial.println(WiFi.softAPIP());
  }
}

void saveWiFiCredentials(String ssid, String password) {
  preferences.putString("ssid", ssid);
  preferences.putString("password", password);
  Serial.println("WiFi credentials saved.");
}

#endif
