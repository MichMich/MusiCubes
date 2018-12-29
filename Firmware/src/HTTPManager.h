#include <Arduino.h>
#include <elapsedMillis.h>
#include "config.h"

#define STATE_UPDATE_INTERVAL 1000
#define HTTP_DEBUG false

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
    PlayStateChangedCallback _playStateChangedCallback;
    elapsedMillis _stateUpdateTimer;
    String _lastState;
    void checkState();
    String serverUrl(String endpoint);
    String makeRequest(String uri);
};