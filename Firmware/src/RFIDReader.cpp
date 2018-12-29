#include "RFIDReader.h"

RFIDReader::RFIDReader() : _mfrc522(MFRC522_SS_PIN, MFRC522_RST_PIN){
  _currentCube = NO_CUBE_IDENTIFIER;
  _checkCount = 0;
}

void RFIDReader::init() {
  SPI.begin();
  _mfrc522.PCD_Reset();
  _mfrc522.PCD_Init();
}

void RFIDReader::handle() {
  if (_readTimer > RFID_READ_INTERVAL) {
    readCube();

    _readTimer = 0;
  }
}

void RFIDReader::setCubeChangeCallback(CubeChangeCallback callback) {
  _cubeChangedCallback = callback;
}

bool RFIDReader::cubePresent() {
  return _currentCube != NO_CUBE_IDENTIFIER;
}

void RFIDReader::readCube() {
  if (_checkCount > RFID_CHECK_REPEAT) {
    changeCubeIfDifferent(NO_CUBE_IDENTIFIER);
    _checkCount = 0;
    return;
  }

  if ( !_mfrc522.PICC_IsNewCardPresent() || !_mfrc522.PICC_ReadCardSerial()) {
    _checkCount++;
		return;
	}

  _checkCount = 0;
  char uid[16];
  sprintf(uid, "%02x:%02x:%02x:%02x", _mfrc522.uid.uidByte[0], _mfrc522.uid.uidByte[1], _mfrc522.uid.uidByte[2], _mfrc522.uid.uidByte[3]);
  changeCubeIfDifferent(String(uid));
}

bool RFIDReader::isChanged(String cubeUID) {
  return strcmp(cubeUID.c_str(), _currentCube.c_str()) != 0;
}

void RFIDReader::cubeChanged(String cubeUID) {
  if (RFID_DEBUG) {
    Serial.println(String("CubeUID: " + cubeUID));
  }
  _currentCube = cubeUID;
  _cubeChangedCallback(cubeUID);
}

void RFIDReader::changeCubeIfDifferent(String cubeUID) {
  if (isChanged(cubeUID)) {
    cubeChanged(cubeUID);
  }
}