#include <esp_now.h>
#include <WiFi.h>
#include <entity/Fountain.h>
#include <parameters.h>

//#define IN_DEBUG_MODE

Fountain *fountain = new Fountain(
    valveCenterPin, valveMiddlePin, valveExternalPin
  , ledPowerPin
  , led1RedPin, led1GreenPin, led1BluePin
  , led2RedPin, led2GreenPin, led2BluePin
  , led3RedPin, led3GreenPin, led3BluePin
  , led4RedPin, led4GreenPin, led4BluePin
  );

unsigned long lastReceivedTime = millis();

void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  #ifdef IN_DEBUG_MODE
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.print("\n\rPacket from: "); Serial.println(macStr);
  #endif
  if (  mac[0] != senderAddress[0]
     || mac[1] != senderAddress[1]
     || mac[2] != senderAddress[2]
     || mac[3] != senderAddress[3]
     || mac[4] != senderAddress[4]
     || mac[5] != senderAddress[5]
    ){
    #ifdef IN_DEBUG_MODE
      Serial.print("\n\rWrong sender: "); Serial.println(macStr);
    #endif
    return;
  }
  lastReceivedTime = millis();
  fountain_state fountainState;
  memcpy(&fountainState, incomingData, sizeof(fountainState));
  fountain->updateState(fountainState);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Fountain LED & valve controller initializing...");
  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing connection!");
    return;
  }
  
  esp_now_register_recv_cb(onDataRecv);
  Serial.println("Fountain LED & valve controller initialized");
}
 
void loop() {
  if (lastReceivedTime + iddleTimeToDemo > millis()) return;
  fountain->showDemo();
}
