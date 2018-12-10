#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include <elapsedMillis.h>
#include "FastLED.h"
#include "LedController.h"
#include "config.h"


#define RST_PIN         D1          // Configurable, see typical pin layout above
#define SS_PIN          D2         // Configurable, see typical pin layout above
#define NUM_LEDS  125
char lastUid[16];
elapsedMillis cardLastSeen;
bool cardPresent = false;

WiFiClient espClient;
PubSubClient client(espClient);
MFRC522 mfrc522(SS_PIN, RST_PIN);
LedController ledController;

void setup() {
    Serial.begin(9600);
    SPI.begin();			// Init SPI bus
    mfrc522.PCD_Init();

    ledController.init();

    WiFiManager wifiManager;
    wifiManager.autoConnect("MusiCubes");
    Serial.println("connected...yeey :)");

    ArduinoOTA.begin();

    randomSeed(micros());
    client.setServer(mqtt_server, 1883);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    // Create a random client ID
    String clientId = "MusiCubes-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password, "musicubes/connected", MQTTQOS2, true, "0")) {
      // Connected
      IPAddress ip = WiFi.localIP();
      client.publish("musicubes/connected","1", true);
      client.publish("musicubes/ip", ip.toString().c_str(), true);
    } else {
      delay(1000);
    }
  }
}

void loop() {
  ArduinoOTA.handle();
  ledController.handle();

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (cardLastSeen > 100 & cardPresent) {
    cardPresent = false;
    lastUid[16] = {0};
    sprintf(lastUid, "00:00:00:00");
    client.publish("musicubes/cube", "00:00:00:00");
    ledController.heatEffect();
  }

  if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

  cardLastSeen = 0;
  cardPresent = true;
  char uid[16];
  sprintf(uid, "%02x:%02x:%02x:%02x", mfrc522.uid.uidByte[0], mfrc522.uid.uidByte[1], mfrc522.uid.uidByte[2], mfrc522.uid.uidByte[3]);

  if (strcmp(uid, lastUid) != 0) {
    client.publish("musicubes/cube", uid);
    strncpy(lastUid, uid, 16);
    ledController.coolEffect();
  }


}