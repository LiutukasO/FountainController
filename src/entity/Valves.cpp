#include <entity/Valves.h>
#include <Arduino.h>

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
    valveState.center = digitalRead(centerPin);
    valveState.middle = digitalRead(middlePin);
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
    return digitalRead(centerPin);
}

void Valves::turnOnCenter(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOnCenter()");
    #endif
    if (digitalRead(centerPin) == LOW) return;
    this->updateTime = millis();
    digitalWrite(centerPin, LOW);
}

void Valves::turnOffCenter(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOffCenter()");
    #endif
    if (digitalRead(centerPin) == HIGH) return;
    this->updateTime = millis();
    digitalWrite(centerPin, HIGH);
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
    return digitalRead(middlePin);
}

void Valves::turnOnMiddle(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOnMiddle()");
    #endif
    if (digitalRead(middlePin) == LOW) return;
    this->updateTime = millis();
    digitalWrite(middlePin, LOW);
}

void Valves::turnOffMiddle(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOffMiddle()");
    #endif
    if (digitalRead(middlePin) == HIGH) return;
    this->updateTime = millis();
    digitalWrite(middlePin, HIGH);
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
    return digitalRead(externalPin);
}

void Valves::turnOnExternal(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOnExternal()");
    #endif
    if (digitalRead(externalPin) == LOW) return;
    this->updateTime = millis();
    digitalWrite(externalPin, LOW);
}

void Valves::turnOffExternal(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOffExternal()");
    #endif
    if (digitalRead(externalPin) == HIGH) return;
    this->updateTime = millis();
    digitalWrite(externalPin, HIGH);
}

void Valves::togleExternal(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::togleExternal()");
    #endif
    this->updateTime = millis();
    digitalWrite(externalPin, !digitalRead(externalPin));
}
