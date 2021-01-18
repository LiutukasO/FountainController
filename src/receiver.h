#include <fountain.h>

fountain_state fountainState;

unsigned char valvePins[] = {15, 4, 5, 18, 19, 21, 22, 23};
unsigned char ledPins[]   = {13, 12, 14, 27, 26, 25, 33, 32};

bool exctractByte(unsigned long int bytes, unsigned char position){
  return (bytes & (0x1 << position)) >> position;
}

void updateValveStatus(unsigned long int valvesState){
  Serial.print("\tValvesState: "); Serial.println(valvesState, BIN);
  for (unsigned char i=0; i < 8; i++){
    bool state = exctractByte(valvesState, i);
    //Serial.print("\tstate["); Serial.print(i, DEC); Serial.print("]: "); Serial.println(state, BIN);
    digitalWrite(valvePins[i], state);
  }
}

void updateLedStatus(unsigned long int ledsState){
  Serial.print("\tLedState: "); Serial.println(ledsState, BIN);
  for (unsigned char i=0; i < 8; i++){
    bool state = exctractByte(ledsState, i);
    //Serial.print("\tstate["); Serial.print(i, DEC); Serial.print("]: "); Serial.println(state, BIN);
    digitalWrite(ledPins[i], state);
  }
}

void onDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  Serial.println("\r\nReceived: ");
  memcpy(&fountainState, incomingData, sizeof(fountainState));
  updateValveStatus(fountainState.valves);
  updateLedStatus(fountainState.leds);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Fountain LED & valve controller initializing...");

  WiFi.mode(WIFI_STA);

  for (unsigned char i = 0; i < 8; i++) {
    pinMode(valvePins[i], OUTPUT);
  }
  
  for (unsigned char i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing connection!");
    return;
  }
  
  esp_now_register_recv_cb(onDataRecv);
  Serial.println("Fountain LED & valve controller initialized");
}
 
void loop() {
}
