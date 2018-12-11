#include "MQTTManager.h"

MQTTManager::MQTTManager() : _client(_espClient) {
}

void MQTTManager::init() {
  randomSeed(micros());
  _client.setServer(_config.mqtt_server, 1883);
  using namespace std::placeholders;
  _client.setCallback(std::bind(&MQTTManager::messageCallback, this, _1, _2, _3));
}

void MQTTManager::handle() {
  checkConnection();
  _client.loop();
}

void MQTTManager::publishCubeIdentifier(String cubeUID) {
  checkConnection();
  _client.publish("musicubes/cube", cubeUID.c_str());
}

void MQTTManager::publishButtonState(uint8_t buttonIndex, bool state) {
  checkConnection();
  String topic = String("musicubes/buttons/" + String(buttonIndex, 10));
  String stateString = state ? "1" : "0";
  _client.publish(topic.c_str(), stateString.c_str());
}

void MQTTManager::setPlayStateChangedCallback(PlayStateChangedCallback callback) {
  _playStateChangedCallback = callback;
}

void MQTTManager::checkConnection() {
  // Loop until we're reconnected
  while (!_client.connected()) {
    // Create a random _client ID
    String clientId = "MusiCubes-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (_client.connect(clientId.c_str(), _config.mqtt_user, _config.mqtt_password, "musicubes/connected", MQTTQOS2, true, "0")) {
      // Connected
      IPAddress ip = WiFi.localIP();
      _client.publish("musicubes/connected","1", true);
      _client.publish("musicubes/ip", ip.toString().c_str(), true);
      _client.subscribe("musicubes/state");
    } else {
      delay(250);
    }
  }
}

void MQTTManager::messageCallback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  if (message == String("PLAYING")) {
    _playStateChangedCallback(Playing);
  } else if (message == String("TRANSITIONING")) {
    _playStateChangedCallback(Transitioning);
  } else {
    _playStateChangedCallback(Stopped);
  }
}