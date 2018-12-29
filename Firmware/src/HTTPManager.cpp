#include "HTTPManager.h"
#include <ESP8266HTTPClient.h>


HTTPManager::HTTPManager() {
}

void HTTPManager::init() {
}

void HTTPManager::handle() {
  if (_stateUpdateTimer > STATE_UPDATE_INTERVAL) {
    checkState();
    _stateUpdateTimer = 0;
  }
}

void HTTPManager::publishCubeIdentifier(String cubeUID) {
  makeRequest("cube/" + cubeUID);
}

void HTTPManager::publishButtonState(uint8_t buttonIndex, bool state) {
  if (!state) return;
  makeRequest("button/" + String(buttonIndex) + "/" + String(state ? "1" : "0"));
}

void HTTPManager::setPlayStateChangedCallback(PlayStateChangedCallback callback) {
  _playStateChangedCallback = callback;
}

void HTTPManager::checkState() {
  String state = makeRequest("state");
  if (state != "" && state != _lastState) {
    Serial.println(state);

    if (state == String("PLAYING")) {
      _playStateChangedCallback(Playing);
    } else if (state == String("TRANSITIONING")) {
      _playStateChangedCallback(Transitioning);
    } else {
      _playStateChangedCallback(Stopped);
    }

    _lastState = state;
  }
}

String HTTPManager::serverUrl(String endpoint) {
  return String("http://") + String(_config.http_server) + ":" + String(_config.http_port) + "/" + endpoint;
}

String HTTPManager::makeRequest(String uri) {
  HTTPClient http;

  String url = serverUrl(uri);
  http.begin(url);
  int responseCode = http.GET();
  String response = responseCode == HTTP_CODE_OK ? http.getString() : "";

  Serial.print(url);
  Serial.print(" (");
  Serial.print(responseCode);
  Serial.print("): ");
  Serial.println(response);

  return response;
}