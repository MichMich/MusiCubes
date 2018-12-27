#include "TouchManager.h"
#include <Wire.h>


#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

TouchManager::TouchManager() {
  Wire.begin(TOUCH_SDA, TOUCH_SCL);
}

void TouchManager::init() {
  if (!_cap.begin(TOUCH_ADR)) {
    Serial.println("MPR121 not found, check wiring?");
  }
  _cap.setThresholds(TOUCH_THRESHOLD_TOUCH, TOUCH_THRESHOLD_RELEASE);
  writeRegister(MPR121_ECR, 0b01000001);
}

void TouchManager::handle() {
  if (_intervalTimer > TOUCH_CHECK_INTERVAL) {
    checkStates();
    _intervalTimer = 0;
  }
  // _buttonChangeCallback(1, true)
}

void TouchManager::setButtonChangeCallback(ButtonChangeCallback callback) {
  _buttonChangeCallback = callback;
}

void TouchManager::checkStates() {
  uint16_t newStates = _cap.touched();
  if (newStates == _lastStates) return;

  // Dirty hack to prevent false positives.
  delay(25);
  if (newStates != _cap.touched()) return;

  for (uint8_t i = 0; i < 12; i++) {
    if ((newStates & _BV(i)) != (_lastStates & _BV(i))) {
      _buttonChangeCallback(i, newStates & _BV(i));
    }
  }
  _lastStates = newStates;
}

void TouchManager::writeRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(TOUCH_ADR);
    Wire.write((uint8_t)reg);
    Wire.write((uint8_t)(value));
    Wire.endTransmission();
}