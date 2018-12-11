#include <Arduino.h>
#include <WiFiManager.h>
#include <PubSubClient.h>
#include "config.h"

enum PlayState {
  Playing,
  Stopped,
  Transitioning
};

typedef void (*PlayStateChangedCallback)(PlayState playState);

class MQTTManager {
  public:
    MQTTManager();
    void init();
    void handle();
    void publishCubeIdentifier(String cubeUID);
    void publishButtonState(uint8_t buttonIndex, bool state);
    void setPlayStateChangedCallback(PlayStateChangedCallback callback);

  private:
    Config _config;
    WiFiClient _espClient;
    PubSubClient _client;
    PlayStateChangedCallback _playStateChangedCallback;
    void checkConnection();
    void messageCallback(char* topic, byte* payload, unsigned int length);
};