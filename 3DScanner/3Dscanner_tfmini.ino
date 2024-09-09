#include "WiFiHandling.h"
#include "LidarHandling.h"
#include "WebServerHandling.h"
#include "SDCardHandling.h"
#include "FactoryResetHandling.h"
#include "ButtonHandling.h"

void setup() {
  Serial.begin(115200);

  initSDCard();        // Initialize SD card
  initWiFi();          // Initialize Wi-Fi and manage AP/STA modes
  setupLidar();        // Setup LiDAR for communication
  startWebServer();    // Start the web server
  setupButton();       // Setup physical button for start/stop scanning
}

void loop() {
  handleLidarData();              // Continuously process LiDAR data
  handleButtonPress();            // Check for physical button press to start/stop scan
}
