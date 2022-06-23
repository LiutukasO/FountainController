#include <dto/valve/Valve.h>
#include <Arduino.h>

//#define IN_DEBUG_MODE

Valve::Valve (unsigned char channel){
    this->channel = channel;
    this->state = MIN_DUTY_CYCLE;
    Serial.printf("\n\t\tValve channel: %d", this->channel);
    this->updateTime = millis();
}

unsigned long Valve::getUpdateTime(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValve::getUpdateTime()");
    #endif
    return this->updateTime;
}

unsigned char Valve::getState(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValve::getState()");
    #endif
    return this->state;
}


void Valve::setState(unsigned char state){
    #ifdef IN_DEBUG_MODE
        Serial.printf("\t\tValve::setState(%d)\n", state);
    #endif
    this->state = state;
    this->updateTime = millis();
}

bool Valve::isOn(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValve::isOn()");
    #endif
    return this->state > MID_DUTY_CYCLE;
}

void Valve::turnOn(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValve::turnOn()");
    #endif
    if (this->state == MAX_DUTY_CYCLE) return;
    this->state = MAX_DUTY_CYCLE;
    this->updateTime = millis();
}

void Valve::turnOff(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValve::turnOff()");
    #endif
    if (this->state == MIN_DUTY_CYCLE) return;
    this->state = MIN_DUTY_CYCLE;
    this->updateTime = millis();
}

void Valve::togle(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValve::togle()");
    #endif
    this->state = 255 - this->state;
    this->updateTime = millis();
}
