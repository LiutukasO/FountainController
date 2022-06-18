#include <esp_now.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <entity/Fountain.h>
#include <parameters.h>
#include <receiver_index.h>

#define IN_DEBUG_MODE

AsyncWebServer server(80);
AsyncEventSource events("/events");

Fountain *fountain;

unsigned long lastReceivedTime = millis();

void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  #ifdef IN_DEBUG_MODE
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.printf("\n\rPacket from: %s\n", macStr);
  #endif
  if (!isValidSender(mac)){
    #ifdef IN_DEBUG_MODE
      Serial.printf("\n\rWrong sender: %s\n", macStr);
    #endif
    return;
  }
  lastReceivedTime = millis();
  fountain_state fountainState;
  memcpy(&fountainState, incomingData, sizeof(fountainState));
  fountain->updateState(fountainState);
  events.send("fountainState", "onDataRecv", millis());
}

void setup() {
  Serial.begin(115200);
  Serial.println("Fountain LED & valve controller initializing...");
  Serial.printf("ESP Board MAC Address: %s\n", WiFi.macAddress().c_str());

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  if (WiFi.status() != WL_CONNECTED) {
    delay(5000);
    Serial.println("Setting as a Wi-Fi Station..");
  }
  Serial.printf("Station IP Address: %s\n", WiFi.localIP().toString().c_str());
  Serial.printf("Wi-Fi Channel: %d\n", WiFi.channel());

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing connection!");
    return;
  }
  
  Serial.println("Fountain initializing...");
  fountain = new Fountain(
    valveChannelGroup
  , led1ChannelGroup
  , led2ChannelGroup
  , led3ChannelGroup
  , led4ChannelGroup
  );
  Serial.println("Fountain initialized.");

  esp_now_register_recv_cb(onDataRecv);


  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html; charset=utf-8", index_html);
  });

  server.on("/fountain/status", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse(200, "application/json", fountain->toJson(fountain->getFountainState()));
    //response->addHeader("Test-Header", "My header value");
    request->send(response);
  });

  events.onConnect([](AsyncEventSourceClient *client){
    if (client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 10000);
  });
  server.addHandler(&events);
  server.begin();
  
  Serial.println("Fountain LED & valve controller initialized");
}
 
void loop() {
  if (lastReceivedTime + iddleTimeToDemo > millis()) return;
  fountain->showDemo();
}
