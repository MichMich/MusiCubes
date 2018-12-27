#include <Arduino.h>
#include "Adafruit_MPR121.h"
#include <elapsedMillis.h>

#define TOUCH_ADR 0x5A
#define TOUCH_SDA D1
#define TOUCH_SCL D2
#define TOUCH_THRESHOLD_TOUCH 1
#define TOUCH_THRESHOLD_RELEASE 30
#define TOUCH_CHECK_INTERVAL 20

typedef void (*ButtonChangeCallback)(uint8_t button, bool state);

class TouchManager {
  public:
    TouchManager();
    void init();
    void handle();
    void setButtonChangeCallback(ButtonChangeCallback callback);

  private:
    elapsedMillis _intervalTimer;
    ButtonChangeCallback _buttonChangeCallback;
    Adafruit_MPR121 _cap = Adafruit_MPR121();
    uint16_t _lastStates;
    void checkStates();
    void writeRegister(uint8_t reg, uint8_t value);
};