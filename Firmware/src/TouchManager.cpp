#include "TouchManager.h"
#include <Wire.h>


#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

TouchManager::TouchManager() {
  Wire.begin(TOUCH_SDA, TOUCH_SCL);
}

void TouchManager::init() {
  configureSensors();
}

void TouchManager::handle() {
  if (_intervalTimer > TOUCH_CHECK_INTERVAL) {
    checkStates();
    _intervalTimer = 0;
  }
}

void TouchManager::setButtonChangeCallback(ButtonChangeCallback callback) {
  _buttonChangeCallback = callback;
}

void TouchManager::configureSensors() {
  for (uint8_t i = 0; i < TOUCH_SENSORS; i++) {
    _sensors[i] = Adafruit_MPR121();
    if (!_sensors[i].begin(_sensorAddresses[i])) {
      Serial.println(String("TouchSensor not found: " + i));
      continue;
    }

    _sensors[i].setThresholds(TOUCH_THRESHOLD_TOUCH, TOUCH_THRESHOLD_RELEASE);
    // _sensors[i].writeRegister();
  }
}

void TouchManager::checkStates() {
  for (uint8_t i = 0; i < TOUCH_SENSORS; i++) {
    uint16_t newState = _sensors[i].touched() & 0b00000001;
    if (newState != _lastStates[i]) {
      _buttonChangeCallback(i, newState);
      _lastStates[i] = newState;
    }
  }
}