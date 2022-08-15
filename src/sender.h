#include <esp_now.h>
#include <WiFi.h>
#include <parameters.h>
#include <entity/FountainManager.h>

#define IN_DEBUG_MODE

volatile unsigned long meter = 0;
volatile unsigned long meterSended = 0;
volatile unsigned long meterTime = 0;

volatile unsigned long fountainStateTime = 0;
fountain_state fountainStateUpdated;

FountainManager fountainManager = FountainManager(audioInputPin);

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t espStatus){
  #ifdef IN_DEBUG_MODE
    Serial.print("Packet Send Status:\t");
    Serial.println(espStatus == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
  #endif
  if (espStatus == ESP_NOW_SEND_SUCCESS){
  // TODO: update Connection Status LED (RED/GREEN)
    meterSended++;
  }
}

bool changedFountainState(fountain_state fountainState) {
  if (fountainStateUpdated.valveState.center != fountainState.valveState.center) return true;
    //Serial.print("\n\t\tVALVE C");
  if (fountainStateUpdated.valveState.ring1  != fountainState.valveState.ring1)  return true;
    //Serial.print("\n\t\tVALVE R1");
  if (fountainStateUpdated.valveState.ring2  != fountainState.valveState.ring2)  return true;
    //Serial.print("\n\t\tVALVE R2");
  if (fountainStateUpdated.valveState.ring3  != fountainState.valveState.ring3)  return true;
    //Serial.print("\n\t\tVALVE R3");

  if (fountainStateUpdated.led1State.red   != fountainState.led1State.red)   return true;
    //Serial.print("\n\t\tLED1 R");
  if (fountainStateUpdated.led1State.green != fountainState.led1State.green) return true;
    //Serial.print("\n\t\tLED1 G");
  if (fountainStateUpdated.led1State.blue  != fountainState.led1State.blue)  return true;
    //Serial.print("\n\t\tLED1 B");

  if (fountainStateUpdated.led2State.red   != fountainState.led2State.red)   return true;
    //Serial.print("\n\t\tLED2 R");
  if (fountainStateUpdated.led2State.green != fountainState.led2State.green) return true;
    //Serial.print("\n\t\tLED2 G");
  if (fountainStateUpdated.led2State.blue  != fountainState.led2State.blue)  return true;
    //Serial.print("\n\t\tLED2 B");

  if (fountainStateUpdated.led3State.red   != fountainState.led3State.red)   return true;
    //Serial.print("\n\t\tLED3 R");
  if (fountainStateUpdated.led3State.green != fountainState.led3State.green) return true;
    //Serial.print("\n\t\tLED3 G");
  if (fountainStateUpdated.led3State.blue  != fountainState.led3State.blue)  return true;
    //Serial.print("\n\t\tLED3 B");
  return false;
}

bool needToUpdateFountainState(fountain_state fountainState){
  if (changedFountainState(fountainState)) {
    #ifdef IN_DEBUG_MODE
      Serial.print("Fountain State changed");
    #endif
    return true;
  }
  if (fountainStateTime + 10000 < millis()) {
    #ifdef IN_DEBUG_MODE
      Serial.print("Need to update Fountain State on Idle");
    #endif
    return true;
  }
  return false;
}

void updateFountainState(fountain_state fountainState){
  #ifdef IN_DEBUG_MODE
    Serial.println("\r\nupdateFountainState");
  #endif
  if (fountainStateTime + 20 > millis()) return;
  if (!needToUpdateFountainState(fountainState)) return;
  Fountain::printFountainState(fountainState);
  #ifdef IN_DEBUG_MODE
    Serial.println("\r\nSending...");
  #endif
  fountainStateTime = millis();
  fountainStateUpdated = fountainState;
  meter++;
  esp_err_t result = esp_now_send(receiverAddress, (uint8_t *)&fountainState, sizeof(fountainState));
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data: "+result);
  }
  #ifdef IN_DEBUG_MODE
    Serial.println("\r\nSending finished!");
  #endif
}

void showDemo(){
    if (fountainStateTime + demoUpdateInterval > millis()) return;
    #ifdef IN_DEBUG_MODE
        Serial.println("\tshowDemo()");
    #endif
    updateFountainState(Fountain::getDemoFountainState(fountainStateUpdated));
}

void processMeter(){
  if (meterTime + 10000 > millis()) return;
  Serial.printf("\n10s Meter: %d / %d", meterSended, meter);
  meterTime = millis();
  meterSended = 0;
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
    Serial.println("Error initializing ESP-NOW!");
    return;
  }
  Serial.println("successfully initialized ESP-NOW.");

  esp_now_register_send_cb(onDataSent);

  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer: "+receiverAddress);
    return;
  }

  // TODO: update Initialization Status LED to GREEN
  Serial.println("Fountain manager initialized");
}

void loop(){
  processMeter();
  // TODO: setup trigers for FountainManager's Audio buttons
  if (fountainManager.isAudioConnected()){
    updateFountainState(fountainManager.getFountainStateFromAudio());
    return;
  }

  // TODO: setup trigers for FountainManager's DMX buttons
  if (fountainManager.isDmxConnected()) {
    updateFountainState(fountainManager.getFountainStateFromDMX());
    return;
  }

  showDemo();
}
