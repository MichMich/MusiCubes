#include <Arduino.h>

typedef void (*ButtonChangeCallback)(uint8_t button, bool state);

class TouchManager {
  public:
    TouchManager();
    void init();
    void handle();
    void setButtonChangeCallback(ButtonChangeCallback callback);

  private:
    ButtonChangeCallback _buttonChangeCallback;
};