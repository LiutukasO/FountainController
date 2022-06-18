#include <Arduino.h>
#include <dmx/dmx.h>

int readcycle = 0;

void setup() {
  Serial.begin(115200);
  DMX::Initialize();
}

void loop()
{
  if(millis() - readcycle > 1000)
  {
    readcycle = millis();

    Serial.print("\n");
    Serial.print(readcycle);
      
    if(DMX::IsHealthy())
    {
      Serial.print(": ok - ");
    }
    else
    {
      Serial.print(": fail - ");
    }
    for (size_t i = 1; i < 21; i++)
    {
        Serial.print(DMX::Read(i));
        Serial.print(" | ");
    }
  }
}