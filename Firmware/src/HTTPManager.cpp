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

void HTTPManager::setPlayStateChangedCallback(PlayStateChangedCallback callback) {
  _playStateChangedCallback = callback;
}

void HTTPManager::changeVolume(VolumeChange change) {
  makeRequest("volume/" + String(change == Up ? "up" : "down"));
}

void HTTPManager::skipSong(SkipDirection direction) {
  makeRequest("skip/" + String(direction == Next ? "next" : "previous"));
}

void HTTPManager::log(String string) {
  makeRequest("log/" + string);
}

void HTTPManager::checkState() {
  String state = makeRequest("state");
  if (state != "" && state != _lastState) {
    Serial.println(state);

    if (state == String("PLAYING")) {
      setPlayState(Playing);
    } else if (state == String("TRANSITIONING")) {
      setPlayState(Transitioning);
    } else {
      setPlayState(Stopped);
    }

    _lastState = state;
  }
}

void HTTPManager::setPlayState(PlayState state) {
  playState = state;
  _playStateChangedCallback(state);
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

  if (HTTP_DEBUG) {
    Serial.print(url);
    Serial.print(" (");
    Serial.print(responseCode);
    Serial.print("): ");
    Serial.println(response);
  }

  return response;
}