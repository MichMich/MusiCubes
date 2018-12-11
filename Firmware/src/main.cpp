#include <ArduinoOTA.h>
#include <WiFiManager.h>

#include "RFIDReader.h"
#include "LedController.h"
#include "MQTTManager.h"
#include "TouchManager.h"

LedController ledController;
RFIDReader rfidReader;
MQTTManager mqttManager;
TouchManager touchManager;

// Define the callbacks. The implementation is at the bottom.
void cubeChanged(String cubeUID);
void buttonChanged(uint8_t buttonIndex, bool state);

// Setup & Loop
void setup() {
  Serial.begin(9600);

  WiFiManager wifiManager;
  wifiManager.autoConnect("MusiCubes");

  ArduinoOTA.begin();

  ledController.init();
  mqttManager.init();
  rfidReader.init();
  touchManager.init();

  rfidReader.setCubeChangeCallback(cubeChanged);
  touchManager.setButtonChangeCallback(buttonChanged);
}

void loop() {
  ArduinoOTA.handle();
  mqttManager.handle();
  rfidReader.handle();
  touchManager.handle();
  ledController.handle();
}

// Callbacks.
void cubeChanged(String cubeUID) {
  Colors colors;

  mqttManager.publishCubeIdentifier(cubeUID);
  if (rfidReader.cubePresent()) {
    ledController.setBaseColor(colors.playing);
    ledController.flashColor(colors.newCube);
  } else {
    ledController.setBaseColor(colors.stopped);
    ledController.flashColor(colors.cubeRemoved);
  }
}

void buttonChanged(uint8_t buttonIndex, bool state) {
  Colors colors;

  mqttManager.publishButtonState(buttonIndex, state);
  ledController.flashColor(colors.buttonPressed);
}