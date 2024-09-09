#ifndef SDCARDHANDLING_H
#define SDCARDHANDLING_H

#include <FS.h>
#include <SD.h>

const int chipSelect = 5;

void initSDCard() {
  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card initialization failed!");
  } else {
    Serial.println("SD Card initialized.");
  }
}

void saveScanData(String data) {
  String dir = "/scans/scan_" + String(millis());
  SD.mkdir(dir);
  File scanFile = SD.open(dir + "/data.txt", FILE_WRITE);
  if (scanFile) {
    scanFile.println(data);
    scanFile.close();
    Serial.println("LiDAR scan data saved.");
  } else {
    Serial.println("Failed to save LiDAR scan data.");
  }
}

void reformatSDCard() {
  if (SD.begin(chipSelect)) {
    File root = SD.open("/");
    while (true) {
      File entry = root.openNextFile();
      if (!entry) break;
      SD.remove(entry.name());
    }
    Serial.println("SD card reformatted.");
  } else {
    Serial.println("Failed to reformat SD card.");
  }
}

#endif
