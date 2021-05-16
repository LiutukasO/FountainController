#include <entity/Valves.h>
#include <Arduino.h>

#define RELAY_ON 0x0
#define RELAY_OFF 0x1
//#define IN_DEBUG_MODE

Valves::Valves (unsigned char centerPin, unsigned char middlePin, unsigned char externalPin){
    this->centerPin = centerPin;
    this->middlePin = middlePin;
    this->externalPin = externalPin;

    pinMode(this->centerPin, OUTPUT);
    pinMode(this->middlePin, OUTPUT);
    pinMode(this->externalPin, OUTPUT);
}

unsigned long Valves::getUpdateTime(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::getUpdateTime()");
    #endif
    return this->updateTime;
}

valve_state Valves::getState(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::getState()");
    #endif
    valve_state valveState;
    valveState.center   = digitalRead(centerPin);
    valveState.middle   = digitalRead(middlePin);
    valveState.external = digitalRead(externalPin);
    return valveState;
}


// **************
// *** CENTER ***
// **************
bool Valves::isOnCenter(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::isOnCenter()");
    #endif
    return digitalRead(centerPin) == RELAY_ON;
}

void Valves::turnOnCenter(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOnCenter()");
    #endif
    if (digitalRead(centerPin) == RELAY_ON) return;
    this->updateTime = millis();
    digitalWrite(centerPin, RELAY_ON);
}

void Valves::turnOffCenter(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOffCenter()");
    #endif
    if (digitalRead(centerPin) == RELAY_OFF) return;
    this->updateTime = millis();
    digitalWrite(centerPin, RELAY_OFF);
}

void Valves::togleCenter(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::togleCenter()");
    #endif
    this->updateTime = millis();
    digitalWrite(centerPin, !digitalRead(centerPin));
}

// **************
// *** MIDDLE ***
// **************
bool Valves::isOnMiddle(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::isOnMiddle()");
    #endif
    return digitalRead(middlePin) == RELAY_ON;
}

void Valves::turnOnMiddle(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOnMiddle()");
    #endif
    if (digitalRead(middlePin) == RELAY_ON) return;
    this->updateTime = millis();
    digitalWrite(middlePin, RELAY_ON);
}

void Valves::turnOffMiddle(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOffMiddle()");
    #endif
    if (digitalRead(middlePin) == RELAY_OFF) return;
    this->updateTime = millis();
    digitalWrite(middlePin, RELAY_OFF);
}

void Valves::togleMiddle(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::togleMiddle()");
    #endif
    this->updateTime = millis();
    digitalWrite(middlePin, !digitalRead(middlePin));
}

// ****************
// *** EXTERNAL ***
// ****************
bool Valves::isOnExternal(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::isOnExternal()");
    #endif
    return digitalRead(externalPin) == RELAY_ON;
}

void Valves::turnOnExternal(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOnExternal()");
    #endif
    if (digitalRead(externalPin) == RELAY_ON) return;
    this->updateTime = millis();
    digitalWrite(externalPin, RELAY_ON);
}

void Valves::turnOffExternal(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOffExternal()");
    #endif
    if (digitalRead(externalPin) == RELAY_OFF) return;
    this->updateTime = millis();
    digitalWrite(externalPin, RELAY_OFF);
}

void Valves::togleExternal(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::togleExternal()");
    #endif
    this->updateTime = millis();
    digitalWrite(externalPin, !digitalRead(externalPin));
}
