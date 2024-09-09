#ifndef FACTORYRESETHANDLING_H
#define FACTORYRESETHANDLING_H

#include "SDCardHandling.h"
extern Preferences preferences;  // Use the same instance from WiFiHandling.h

void factoryReset(bool reformatSD = false) {
  preferences.clear();  // Clear all saved settings
  if (reformatSD) {
    reformatSDCard();  // Reformat the SD card if specified
  }
  Serial.println("Factory reset complete. Restarting...");
  ESP.restart();  // Restart the ESP32
}

#endif
