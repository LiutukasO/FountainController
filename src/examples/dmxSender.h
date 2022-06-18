#include <Arduino.h>
#include <dmx/ESPDMX.h>

long sendTime = 0;
unsigned char sendValue = 0;

DMXESPSerial dmx;

void setup()
{
  //Serial.begin(115200);

  dmx.init(); // initialization for complete bus

  dmx.write(1, 254);
  dmx.write(2, 254);
  dmx.write(3, 0);
  dmx.write(4, 254);
  dmx.write(5, 254);
  dmx.write(17, 254);
  dmx.write(19, 254);
}

void loop()
{
  dmx.update();
  delay(5);
}