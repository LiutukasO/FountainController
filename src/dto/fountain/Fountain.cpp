#include <dto/fountain/Fountain.h>

#define IN_DEBUG_MODE

Fountain::Fountain (
              unsigned char valveChannel
            , unsigned char ledChannelGroup
){
    this->valve = new Valve(valveChannel);
    this->led = new Led(ledChannelGroup);
}

unsigned long Fountain::getUpdateTime(){
    return this->updateTime;
}

Valve * Fountain::getValve(){
    return this->valve;
}

Led * Fountain::getLed(){
    return this->led;
}

void Fountain::setState(fountain_state fountainState){
    #ifdef IN_DEBUG_MODE
        Serial.println("\tFountain::setState()");
    #endif
    this->valve->setState(fountainState.valve);
    this->led->setRedState(fountainState.led.red);
    this->led->setGreenState(fountainState.led.green);
    this->led->setBlueState(fountainState.led.blue);
    this->updateTime = millis();
}

fountain_state Fountain::getState(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\tFountain::getState()");
    #endif
    fountain_state fountainState;
    fountainState.valve = this->valve->getState();
    fountainState.led = this->led->getState();
    return fountainState;
}

void Fountain::updateValve(unsigned char valveState){
    #ifdef IN_DEBUG_MODE
        Serial.print("\tValve: "); Serial.println(valveState, DEC);
    #endif
    this->valve->setState(valveState);
}

void Fountain::updateLed(led_state ledState){
    #ifdef IN_DEBUG_MODE
        Serial.printf("\tLed: %d %d %d \n", ledState.red, ledState.green, ledState.blue);
    #endif
    this->led->setState(ledState);
}