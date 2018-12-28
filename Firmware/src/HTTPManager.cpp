#include "HTTPManager.h"

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
  String url = serverUrl("cube/" + cubeUID);
  Serial.println(url);
  _http.begin(url);
  Serial.println(_http.GET());
}

void HTTPManager::publishButtonState(uint8_t buttonIndex, bool state) {
  if (!state) return;

  String url = serverUrl("button/" + String(buttonIndex) + "/" + String(state ? "1" : "0"));
  _http.begin(url);
  _http.GET();
}

void HTTPManager::setPlayStateChangedCallback(PlayStateChangedCallback callback) {
  _playStateChangedCallback = callback;
}

void HTTPManager::checkState() {
  String url = serverUrl("state");
  _http.begin(url);
  if (_http.GET() == HTTP_CODE_OK) {
    String state = _http.getString();
    if (state != _lastState) {
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


}

String HTTPManager::serverUrl(String endpoint) {
  return String("http://") + String(_config.http_server) + ":" + String(_config.http_port) + "/" + endpoint;
}
