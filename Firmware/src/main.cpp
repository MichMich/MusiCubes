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
void playStateChanged(PlayState playState);

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
  mqttManager.setPlayStateChangedCallback(playStateChanged);
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
    ledController.setBaseColor(colors.newCube);
  } else {
    ledController.setBaseColor(colors.cubeRemoved);
  }
}

void playStateChanged(PlayState playState) {
  Colors colors;

  switch (playState) {
    case Playing:
      ledController.setBaseColor(colors.playing);
    break;
    case Transitioning:
      ledController.setBaseColor(colors.transitioning);
    default:
      ledController.setBaseColor(colors.stopped);
    break;
  }
}

void buttonChanged(uint8_t buttonIndex, bool state) {
  Colors colors;

  mqttManager.publishButtonState(buttonIndex, state);
  ledController.flashColor(colors.buttonPressed);
}