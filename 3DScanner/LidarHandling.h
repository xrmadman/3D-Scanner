#ifndef LIDARHANDLING_H
#define LIDARHANDLING_H

#include <HardwareSerial.h>
#include "SDCardHandling.h"

HardwareSerial lidarSerial(1);

void setupLidar() {
  lidarSerial.begin(115200, SERIAL_8N1, 16, 17);  // Set up LiDAR communication
  Serial.println("LiDAR setup completed.");
}

void handleLidarData() {
  if (lidarSerial.available()) {
    String lidarData = lidarSerial.readStringUntil('\n');
    Serial.println("LiDAR Data: " + lidarData);
    saveScanData(lidarData);  // Save data to SD card
  }
}

#endif
