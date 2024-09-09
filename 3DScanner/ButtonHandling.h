#ifndef BUTTONHANDLING_H
#define BUTTONHANDLING_H

#include <Arduino.h>
#include "LidarHandling.h"

const int buttonPin = 14;  // Physical button pin
bool scanInProgress = false;

void IRAM_ATTR handleButtonPress();  // Declare the button press handler

void setupButton() {
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(buttonPin, handleButtonPress, FALLING);
  Serial.println("Button setup complete.");
}

void IRAM_ATTR handleButtonPress() {
  scanInProgress = !scanInProgress;
  if (scanInProgress) {
    Serial.println("Scan started via button.");
    // Code to start scan
  } else {
    Serial.println("Scan stopped via button.");
    // Code to stop scan
  }
}

#endif
