#include <Arduino.h>
#include <dmx/ESPDMX.h>

DMXESPSerial dmx;

void setup() {
  Serial.begin(115200);

  delay(3000);

  Serial.println("starting...");

  dmx.init();           // initialization for complete bus

  Serial.println("initialized...");
  delay(200);               // wait a while (not necessary)
}

void loop() {

  for (int channel = 0; channel < 16; channel++)
  {
    dmx.update();
    int value = dmx.read(channel);
    Serial.printf("Channel %d: %d\n", channel, value);
  }
  delay(5000);

}