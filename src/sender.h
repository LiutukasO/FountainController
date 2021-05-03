#include <esp_now.h>
#include <WiFi.h>
#include <parameters.h>
#include <entity/FountainManager.h>

#define IN_DEBUG_MODE

unsigned long fountainStateTime = 0;
FountainManager fountainManager = FountainManager(audioInputPin);

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t espStatus){
  #ifdef IN_DEBUG_MODE
    Serial.print("Packet Send Status:\t");
    Serial.println(espStatus == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
  #endif
  // TODO: update Connection Status LED (RED/GREEN)
  if (espStatus == ESP_NOW_SEND_SUCCESS){
    fountainStateTime = millis();
  }
}

void updateFountainState(fountain_state fountainState){
  #ifdef IN_DEBUG_MODE
    Serial.println("\r\nSending... ");
    Fountain::printFountainState(fountainState);
  #endif
  esp_now_send(receiverAddress, (uint8_t *)&fountainState, sizeof(fountainState));
}

fountain_state showDemo(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\tFountain::showDemo()");
    #endif
    if (fountainStateTime + 1000 > millis()) return;
    updateFountainState(Fountain::getDemoFountainState());
}

void setup(){
  Serial.begin(115200);
  Serial.println("Fountain manager initializing...");
  // TODO: update Initialization Status LED to RED
  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK){
    Serial.println("Error initializing connection!");
    return;
  }
  Serial.println("successfully connected.");

  esp_now_register_send_cb(onDataSent);

  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  // TODO: update Initialization Status LED to GREEN
  Serial.println("Fountain manager initialized");
}

void loop(){
  // TODO: setup trigers for FountainManager's buttons
  if (fountainManager.isAudioConnected()){
    updateFountainState(fountainManager.getFountainStateFromAudio());
    return;
  }
  showDemo();
}
