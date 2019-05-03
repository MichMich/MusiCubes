#include <ArduinoOTA.h>
#include <WiFiManager.h>

#include "RFIDReader.h"
#include "LedController.h"
#include "HTTPManager.h"
#include "TouchManager.h"

#define TOUCH_IGNORE_AFTER_CUBE_CHANGE 1000

LedController ledController;
RFIDReader rfidReader;
HTTPManager httpManager;
TouchManager touchManager;

// Define the callbacks. The implementation is at the bottom.
void cubeChanged(String cubeUID);
void buttonPressed(uint8_t buttonIndex, bool state);
void playStateChanged(PlayState playState);

// Setup & Loop
void setup() {
  Serial.begin(9600);
  ledController.init();

  WiFiManager wifiManager;
  wifiManager.autoConnect("MusiCubes");

  ArduinoOTA.begin();

  httpManager.init();
  rfidReader.init();
  touchManager.init();

  rfidReader.setCubeChangeCallback(cubeChanged);
  touchManager.setButtonPressCallback(buttonPressed);
  httpManager.setPlayStateChangedCallback(playStateChanged);

  httpManager.log("Booted");
}

void loop() {
  ArduinoOTA.handle();
  httpManager.handle();
  rfidReader.handle();
  touchManager.handle();
  ledController.handle();
}

// Callbacks.
void cubeChanged(String cubeUID) {
  Colors colors;

  httpManager.publishCubeIdentifier(cubeUID);
  if (rfidReader.cubePresent()) {
    ledController.flashColor(colors.newCube);
  } else {
    ledController.flashColor(colors.cubeRemoved);
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

void buttonPressed(uint8_t buttonIndex, bool longPress) {
  Colors colors;

  if (rfidReader.changeTimer < TOUCH_IGNORE_AFTER_CUBE_CHANGE) {
    Serial.println("Touch ignored because the cube has recently changed.");
    return;
  }

  /*
  if (httpManager.playState != Playing) {
    Serial.println("Not playing. Ignore button press.");
    ledController.flashColor(colors.cubeRemoved);
    return;
  }
  */

  if (!longPress) {
    httpManager.changeVolume(buttonIndex == 0 ? Up : Down);
    ledController.flashColor(buttonIndex == 0 ? colors.volumeUp : colors.volumeDown);
  } else {
    httpManager.skipSong(buttonIndex == 0 ? Next : Previous);
    ledController.flashColor(buttonIndex == 0 ? colors.nextSong : colors.previousSong);
  }
}