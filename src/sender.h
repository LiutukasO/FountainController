#include <esp_now.h>
#include <WiFi.h>
#include <parameters.h>
#include <entity/FountainManager.h>

//#define IN_DEBUG_MODE

volatile unsigned long meter = 0;
volatile unsigned long meterTime = 0;

volatile unsigned long fountainStateTime = 0;

FountainManager fountainManager = FountainManager(audioInputPin);

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t espStatus){
  #ifdef IN_DEBUG_MODE
    Serial.print("Packet Send Status:\t");
    Serial.println(espStatus == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
  #endif
  if (espStatus == ESP_NOW_SEND_SUCCESS){
  // TODO: update Connection Status LED (RED/GREEN)
    meter++;
  }
}

void updateFountainState(fountain_state fountainState){
  #ifdef IN_DEBUG_MODE
    Serial.println("\r\nSending... ");
    Fountain::printFountainState(fountainState);
  #endif
  fountainStateTime = millis();
  esp_now_send(receiverAddress, (uint8_t *)&fountainState, sizeof(fountainState));
}

void showDemo(){
    if (fountainStateTime + demoUpdateInterval > millis()) return;
    #ifdef IN_DEBUG_MODE
        Serial.println("\tFountain::showDemo()");
    #endif
    updateFountainState(Fountain::getDemoFountainState());
}

void processMeter(){
  if (meterTime + 10000 > millis()) return;
  Serial.print("10s Meter: ");
  Serial.println(meter, DEC);
  meterTime = millis();
  meter = 0;
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
  processMeter();
  // TODO: setup trigers for FountainManager's buttons
  if (fountainManager.isAudioConnected()){
    updateFountainState(fountainManager.getFountainStateFromAudio());
    return;
  }
  showDemo();
}
