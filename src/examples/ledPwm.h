#include <Arduino.h>

// the number of the LED pin
const unsigned char ledPin = 22;  // 16 corresponds to GPIO16

// setting PWM properties
const double freq = 5000;
const unsigned char ledChannel = 0;
const unsigned char resolution = 8;
 
void setup(){
   Serial.begin(115200);
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);
}
 
void loop(){
  Serial.println("UP");
  // increase the LED brightness
  for(unsigned char dutyCycle = 0; dutyCycle < 255; dutyCycle++){   
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);
    //Serial.printf("UP dutyCycle: %d\n", dutyCycle);
    delay(20);
  }

  // decrease the LED brightness
  Serial.println("DOWN");
  for(unsigned char dutyCycle = 255; dutyCycle > 0; dutyCycle--){
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);   
    //Serial.printf("DOWN dutyCycle: %d\n", dutyCycle);
    delay(40);
  }
}
