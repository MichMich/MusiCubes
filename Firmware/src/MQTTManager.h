#include <Arduino.h>
#include <WiFiManager.h>
#include <PubSubClient.h>
#include "config.h"


class MQTTManager {
  public:
    MQTTManager();
    void init();
    void handle();
    void publishCubeIdentifier(String cubeUID);
    void publishButtonState(uint8_t buttonIndex, bool state);

  private:
    Config _config;
    WiFiClient _espClient;
    PubSubClient _client;
    void checkConnection();
};