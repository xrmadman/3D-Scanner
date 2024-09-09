#ifndef WEBSERVERHANDLING_H
#define WEBSERVERHANDLING_H

#include <ESPAsyncWebServer.h>
#include "SDCardHandling.h"
#include "FactoryResetHandling.h"
#include "WiFiHandling.h"

AsyncWebServer server(80);

void startWebServer() {
  // Serve the home page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/html", "Welcome to the ESP32 Web Server!");
  });

  // WiFi settings update
  server.on("/update_wifi", HTTP_POST, [](AsyncWebServerRequest * request) {
    if (request->hasParam("ssid") && request->hasParam("password")) {
      String newSSID = request->getParam("ssid")->value();
      String newPassword = request->getParam("password")->value();
      saveWiFiCredentials(newSSID, newPassword);
      request->send(200, "text/html", "WiFi credentials updated. Restart to connect.");
    } else {
      request->send(400, "text/html", "Invalid WiFi parameters.");
    }
  });

  // Handle factory reset
  server.on("/factory_reset", HTTP_POST, [](AsyncWebServerRequest * request) {
    if (request->hasParam("resetType")) {
      String resetType = request->getParam("resetType")->value();
      if (resetType == "soft") {
        factoryReset(false);
      } else if (resetType == "hard") {
        factoryReset(true);
      }
      request->send(200, "text/html", "Factory reset initiated.");
    } else {
      request->send(400, "text/html", "Invalid request.");
    }
  });

  server.begin();
  Serial.println("Web server started.");
}

#endif
