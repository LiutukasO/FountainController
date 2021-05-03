#include <entity/Fountain.h>
#include <Arduino.h>
#include <parameters.h>

//#define IN_DEBUG_MODE

Fountain::Fountain (
              unsigned char valveCenterPin, unsigned char valveMiddlePin, unsigned char valveExternalPin
            , unsigned char ledPowerPin
            , unsigned char led1RedPin, unsigned char led1GreenPin, unsigned char led1BluePin
            , unsigned char led2RedPin, unsigned char led2GreenPin, unsigned char led2BluePin
            , unsigned char led3RedPin, unsigned char led3GreenPin, unsigned char led3BluePin
            , unsigned char led4RedPin, unsigned char led4GreenPin, unsigned char led4BluePin
){
    this->valves = new Valves(valveCenterPin, valveMiddlePin, valveExternalPin);
    this->led1 = new Led(needToFlushLeds, ledPowerPin, led1RedPin, led1GreenPin, led1BluePin);
    this->led2 = new Led(needToFlushLeds, ledPowerPin, led2RedPin, led2GreenPin, led2BluePin);
    this->led3 = new Led(needToFlushLeds, ledPowerPin, led3RedPin, led3GreenPin, led3BluePin);
    this->led4 = new Led(needToFlushLeds, ledPowerPin, led4RedPin, led4GreenPin, led4BluePin);
}

unsigned long Fountain::getUpdateTime(){
    return this->updateTime;
}

Valves * Fountain::getValves(){
    return this->valves;
}

Led * Fountain::getLed1(){
    return this->led1;
}

Led * Fountain::getLed2(){
    return this->led2;
}

Led * Fountain::getLed3(){
    return this->led3;
}

Led * Fountain::getLed4(){
    return this->led4;
}

void Fountain::printFountainState(fountain_state fountainState){
    #ifdef IN_DEBUG_MODE
        Serial.print("\tvalves: "); Serial.print(fountainState.valveState.center, BIN); Serial.print(fountainState.valveState.middle, BIN); Serial.println(fountainState.valveState.external, BIN);
        Serial.print("\tled 1:  "); Serial.print(fountainState.led1State.red, BIN); Serial.print(fountainState.led1State.green, BIN); Serial.println(fountainState.led1State.blue, BIN);
        Serial.print("\tled 2:  "); Serial.print(fountainState.led2State.red, BIN); Serial.print(fountainState.led2State.green, BIN); Serial.println(fountainState.led2State.blue, BIN);
        Serial.print("\tled 3:  "); Serial.print(fountainState.led3State.red, BIN); Serial.print(fountainState.led3State.green, BIN); Serial.println(fountainState.led3State.blue, BIN);
        Serial.print("\tled 4:  "); Serial.print(fountainState.led4State.red, BIN); Serial.print(fountainState.led4State.green, BIN); Serial.println(fountainState.led4State.blue, BIN);
    #endif
}

fountain_state Fountain::getDemoFountainState(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\tgetDemoFountainState()");
    #endif
    fountain_state fountainState;

    fountainState.valveState.center   = rand() % 2;
    fountainState.valveState.middle   = rand() % 2;
    fountainState.valveState.external = rand() % 2;
    if (!fountainState.valveState.middle && !fountainState.valveState.external){
        fountainState.valveState.center = true;
    }

    // ***** LEDs in CENTER
    if (fountainState.valveState.center){
      fountainState.led1State.red   = rand() % 2;
      fountainState.led1State.green = rand() % 2;
      fountainState.led1State.blue  = rand() % 2;
      if (!fountainState.led1State.red && !fountainState.led1State.green && !fountainState.led1State.red){
        fountainState.led1State.red   = true;
        fountainState.led1State.green = true;
        fountainState.led1State.blue  = true;
      }
    } else {
      fountainState.led1State.red   = false;
      fountainState.led1State.green = false;
      fountainState.led1State.blue  = false;
    }

    // ***** LEDs in MIDDLE
    if (fountainState.valveState.middle){
      fountainState.led2State.red   = rand() % 2;
      fountainState.led2State.green = rand() % 2;
      fountainState.led2State.blue  = rand() % 2;
      if (!fountainState.led2State.red && !fountainState.led2State.green && !fountainState.led2State.red){
        fountainState.led2State.red   = true;
        fountainState.led2State.green = true;
        fountainState.led2State.blue  = true;
      }
    } else {
        fountainState.led2State.red   = false;
        fountainState.led2State.green = false;
        fountainState.led2State.blue  = false;
    }

    // ***** LEDs in MIDDLE
    if (fountainState.valveState.external){
      fountainState.led3State.red   = rand() % 2;
      fountainState.led3State.green = rand() % 2;
      fountainState.led3State.blue  = rand() % 2;
      if (!fountainState.led3State.red && !fountainState.led3State.green && !fountainState.led3State.red){
        fountainState.led3State.red   = true;
        fountainState.led3State.green = true;
        fountainState.led3State.blue  = true;
      }
    } else {
      fountainState.led3State.red   = false;
      fountainState.led3State.green = false;
      fountainState.led3State.blue  = false;
    }
    fountainState.led4State.red   = fountainState.led3State.red;
    fountainState.led4State.green = fountainState.led3State.green;
    fountainState.led4State.blue  = fountainState.led3State.blue;

    return fountainState;
}

void Fountain::showDemo(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\tFountain::showDemo()");
    #endif
    if (updateTime + 1000 > millis()) return;
    this->updateState(Fountain::getDemoFountainState());
}

void Fountain::updateState(fountain_state fountainState){
    #ifdef IN_DEBUG_MODE
        Serial.println("\tFountain::updateState()");
    #endif
    this->updateValves(fountainState.valveState);
    this->updateLeds(this->getLed1(), fountainState.led1State);
    this->updateLeds(this->getLed2(), fountainState.led2State);
    this->updateLeds(this->getLed3(), fountainState.led3State);
    this->updateLeds(this->getLed4(), fountainState.led4State);
    this->flushLeds();
    this->updateTime = millis();
}

void Fountain::flushLeds(){
    this->getLed1()->flush();
    this->getLed2()->flush();
    this->getLed3()->flush();
    this->getLed4()->flush();
}

void Fountain::updateValves(valve_state valveState){
    #ifdef IN_DEBUG_MODE
        Serial.print("\tValves Center: "); Serial.println(valveState.center, BIN);
        Serial.print("\tValves Middle: "); Serial.println(valveState.middle, BIN);
        Serial.print("\tValves External: "); Serial.println(valveState.external, BIN);
    #endif
    Valves *valves = this->getValves();
    if (valveState.center) valves->turnOnCenter(); else valves->turnOffCenter();
    if (valveState.middle) valves->turnOnMiddle(); else valves->turnOffMiddle();
    if (valveState.external) valves->turnOnExternal(); else valves->turnOffExternal();
}

void Fountain::updateLeds(Led *led, led_state ledState){
    #ifdef IN_DEBUG_MODE
        Serial.print("\tLed: ");
        Serial.print(ledState.red, BIN);
        Serial.print(ledState.green, BIN);
        Serial.println(ledState.blue, BIN);
    #endif
    if (ledState.red) led->turnOnRed(); else led->turnOffRed();
    if (ledState.green) led->turnOnGreen(); else led->turnOffGreen();
    if (ledState.blue) led->turnOnBlue(); else led->turnOffBlue();
}

fountain_state Fountain::getFountainState(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\tFountain::getFountainState()");
    #endif
    fountain_state fountainState;
    fountainState.valveState = this->getValves()->getState();
    fountainState.led1State = this->getLed1()->getState();
    fountainState.led2State = this->getLed2()->getState();
    fountainState.led3State = this->getLed3()->getState();
    fountainState.led4State = this->getLed4()->getState();
    return fountainState;
}
