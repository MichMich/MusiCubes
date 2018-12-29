#include <Arduino.h>
#include "Adafruit_MPR121.h"
#include <elapsedMillis.h>

#define TOUCH_SDA D1
#define TOUCH_SCL D2
#define TOUCH_SENSORS 2
#define TOUCH_THRESHOLD_TOUCH 255
#define TOUCH_THRESHOLD_RELEASE 250
#define TOUCH_CHECK_INTERVAL 25

typedef void (*ButtonChangeCallback)(uint8_t button, bool state);

class TouchManager {
  public:
    TouchManager();
    void init();
    void handle();
    void setButtonChangeCallback(ButtonChangeCallback callback);

  private:
    uint16_t _sensorAddresses[TOUCH_SENSORS] = {0x5A, 0x5B};
    bool _lastStates[TOUCH_SENSORS];
    elapsedMillis _intervalTimer;
    ButtonChangeCallback _buttonChangeCallback;
    Adafruit_MPR121 _sensors[TOUCH_SENSORS];
    void configureSensors();
    void checkStates();
};