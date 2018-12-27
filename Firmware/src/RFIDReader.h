#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <elapsedMillis.h>

#define MFRC522_RST_PIN D3
#define MFRC522_SS_PIN  D4

#define RFID_READ_INTERVAL 100
#define RFID_CHECK_REPEAT 3
#define NO_CUBE_IDENTIFIER "00:00:00:00"

typedef void (*CubeChangeCallback)(String cubeUID);

class RFIDReader {
  public:
    RFIDReader();
    void init();
    void handle();
    void setCubeChangeCallback(CubeChangeCallback callback);
    bool cubePresent();

  private:
    MFRC522 _mfrc522;
    elapsedMillis _readTimer;
    String _currentCube;
    CubeChangeCallback _cubeChangedCallback;
    int8_t _checkCount;
    void readCube();
    bool isChanged(String cubeUID);
    void cubeChanged(String cubeUID);
    void changeCubeIfDifferent(String cubeUID);
};