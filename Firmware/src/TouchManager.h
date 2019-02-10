#include <Arduino.h>
#include "Adafruit_MPR121.h"
#include <elapsedMillis.h>

#define TOUCH_DEBUG true

#define TOUCH_SDA D1
#define TOUCH_SCL D2
#define TOUCH_SENSORS 2
#define TOUCH_THRESHOLD_TOUCH 255
#define TOUCH_THRESHOLD_RELEASE 1
#define TOUCH_CHECK_INTERVAL 5

#define TOUCH_SHORTPRESS 50
#define TOUCH_LONGPRESS 500

typedef void (*ButtonPressCallback)(uint8_t button, bool longPress);

class TouchManager {
  public:
    TouchManager();
    void init();
    void handle();
    void setButtonPressCallback(ButtonPressCallback callback);

  private:
    uint16_t _sensorAddresses[TOUCH_SENSORS] = {0x5A, 0x5B};
    bool _lastStates[TOUCH_SENSORS];
    elapsedMillis _intervalTimer;
    elapsedMillis _touchTimers[TOUCH_SENSORS];
    ButtonPressCallback _buttonPressCallback;
    Adafruit_MPR121 _sensors[TOUCH_SENSORS];
    void configureSensors();
    void checkStates();
};