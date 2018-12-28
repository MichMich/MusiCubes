#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <elapsedMillis.h>
#include "config.h"

#define STATE_UPDATE_INTERVAL 2500

enum PlayState {
  Playing,
  Stopped,
  Transitioning
};

typedef void (*PlayStateChangedCallback)(PlayState playState);

class HTTPManager {
  public:
    HTTPManager();
    void init();
    void handle();
    void publishCubeIdentifier(String cubeUID);
    void publishButtonState(uint8_t buttonIndex, bool state);
    void setPlayStateChangedCallback(PlayStateChangedCallback callback);

  private:
    Config _config;
    HTTPClient _http;
    PlayStateChangedCallback _playStateChangedCallback;
    String serverUrl(String endpoint);
    elapsedMillis _stateUpdateTimer;
    String _lastState;
    void checkState();
};