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

void TouchManager::setButtonPressCallback(ButtonPressCallback callback) {
  _buttonPressCallback = callback;
}

void TouchManager::configureSensors() {
  for (uint8_t i = 0; i < TOUCH_SENSORS; i++) {
    _sensors[i] = Adafruit_MPR121();
    if (!_sensors[i].begin(_sensorAddresses[i])) {
      Serial.println(String("TouchSensor not found: " + i));
      continue;
    }

    _sensors[i].setThresholds(TOUCH_THRESHOLD_TOUCH, TOUCH_THRESHOLD_RELEASE);
    _sensors[i].writeRegister(MPR121_ECR, 0b00000001); // Only activate sensor 0.
    _sensors[i].writeRegister(MPR121_DEBOUNCE, 0b01110111); // Maximum Debounce
    _sensors[i].writeRegister(MPR121_CONFIG1, 0b11111111);
    _sensors[i].writeRegister(MPR121_CONFIG2, 0b11111000);
  }
}

void TouchManager::checkStates() {
  for (uint8_t i = 0; i < TOUCH_SENSORS; i++) {
    uint16_t newState = _sensors[i].touched() & 0b00000001;
    if (newState != _lastStates[i]) {
      if (newState == 0) {
        if (_touchTimers[i] >= TOUCH_SHORTPRESS) {
          _buttonPressCallback(i, _touchTimers[i] >= TOUCH_LONGPRESS);
          if (TOUCH_DEBUG) Serial.println("Button " + String(i) + " released after " + String(_touchTimers[i]) + " ms. Longpress: " + String(_touchTimers[i] >= TOUCH_LONGPRESS));
        } else {
          if (TOUCH_DEBUG) Serial.println("Button " + String(i) + " ignored. Too short: " + String(_touchTimers[i]) + " ms");
        }
      }

      _touchTimers[i] = 0;
      _lastStates[i] = newState;
    }
  }
}