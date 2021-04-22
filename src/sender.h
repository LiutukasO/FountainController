//#define IN_DEBUG_MODE

#include <audioSpectrumAnalyzer.h>
#include <fountain.h>

#define ledTreshold 25
#define valveTreshold 15

fountain_state fountainState;

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t espStatus){
  #ifdef IN_DEBUG_MODE
    Serial.print("Packet Send Status:\t");
    Serial.println(espStatus == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
  #endif
}

void updateFountainState(fountain_state fountainState){
  #ifdef IN_DEBUG_MODE
    Serial.println("\r\nSending... ");
    printFountainState(fountainState);
  #endif
  esp_now_send(receiverAddress, (uint8_t *)&fountainState, sizeof(fountainState));
}

void setup(){
  Serial.begin(115200);
  Serial.println("Fountain manager initializing...");
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

  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
  Serial.println("Fountain manager initialized");
}

bool getState(int value, int threshold){
  int dmax = 50;
  value /= amplitude;
  if (value > dmax) value = dmax;
  return value > threshold;
}


void updateState(fountain_state state, char position, int value){
  if (getState(value, ledTreshold)){
    state.leds |= 1 << position;
  } else {
    state.leds &= ~(1 << position);
  }
  if (getState(value, valveTreshold)){
    state.valves |= 1 << position;
  } else {
    state.valves &= ~(1 << position);
  }
  #ifdef IN_DEBUG_MODE
    printFountainState(state);
  #endif
}

fountain_state makeFountainStatus(){
  fountain_state state;
  for (int i = 2; i < (SAMPLES/2); i++){ // Don't use sample 0 and only the first SAMPLES/2 are usable.
    // Each array element represents a frequency and its value, is the amplitude. Note the frequencies are not discrete.
    if (vReal[i] > 1500) { // Add a crude noise filter, 10 x amplitude or more
      if (i<=2 )             updateState(state, 0, (int)vReal[i]); // 125Hz
      if (i >2   && i<=4 )   updateState(state, 1, (int)vReal[i]); // 250Hz
      if (i >4   && i<=7 )   updateState(state, 2, (int)vReal[i]); // 500Hz
      if (i >7   && i<=15 )  updateState(state, 3, (int)vReal[i]); // 1000Hz
      if (i >15  && i<=40 )  updateState(state, 4, (int)vReal[i]); // 2000Hz
      if (i >40  && i<=70 )  updateState(state, 5, (int)vReal[i]); // 4000Hz
      if (i >70  && i<=288 ) updateState(state, 6, (int)vReal[i]); // 8000Hz
      if (i >288           ) updateState(state, 7, (int)vReal[i]); // 16000Hz
    }
  }
  return state;
}

fountain_state getDemoState(){
  fountain_state demoState;
  demoState.leds = rand();
  demoState.valves = rand();
  return demoState;
}

void loop(){
  //makeSamples();
  //transformSamples();
  //fountainState = makeFountainStatus();
  fountainState = getDemoState();
  updateFountainState(fountainState);
}
