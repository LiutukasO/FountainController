#include <entity/Valves.h>
#include <Arduino.h>

//#define IN_DEBUG_MODE

Valves::Valves (unsigned char channelGroup, unsigned char centerPin, unsigned char middlePin, unsigned char externalPin){
    this->centerPin = centerPin;
    this->centerChannel = channelGroup + 1;
    this->centerState = MIN_DUTY_CYCLE;
    ledcAttachPin(this->centerPin, this->centerChannel);
    ledcSetup(this->centerChannel, PWM_FREQ, this->centerState);

    this->middlePin = middlePin;
    this->middleChannel = channelGroup + 2;
    this->middleState = MIN_DUTY_CYCLE;
    ledcAttachPin(this->middlePin, this->middleChannel);
    ledcSetup(this->middleChannel, PWM_FREQ, this->middleState);

    this->externalPin = externalPin;
    this->externalChannel = channelGroup + 3;
    this->externalState = MIN_DUTY_CYCLE;
    ledcAttachPin(this->externalPin, this->externalChannel);
    ledcSetup(this->externalChannel, PWM_FREQ, this->externalState);
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
    valveState.center   = this->centerState;
    valveState.middle   = this->middleState;
    valveState.external = this->externalState;
    return valveState;
}


// **************
// *** CENTER ***
// **************
void Valves::setCenterState(unsigned char state){
    #ifdef IN_DEBUG_MODE
        Serial.printf("\t\tValves::setCenterState(%d)\n", state);
    #endif
    this->centerState = state;
    ledcWrite(this->centerChannel, state);
    this->updateTime = millis();
}

bool Valves::isCenterOn(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::isCenterOn()");
    #endif
    return this->centerState > MID_DUTY_CYCLE;
}

void Valves::turnOnCenter(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOnCenter()");
    #endif
    if (this->centerState == MAX_DUTY_CYCLE) return;
    this->centerState = MAX_DUTY_CYCLE;
    ledcWrite(this->centerChannel, MAX_DUTY_CYCLE);
    this->updateTime = millis();
}

void Valves::turnOffCenter(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOffCenter()");
    #endif
    if (this->centerState == MIN_DUTY_CYCLE) return;
    this->centerState = MIN_DUTY_CYCLE;
    ledcWrite(this->centerChannel, MIN_DUTY_CYCLE);
    this->updateTime = millis();
}

void Valves::togleCenter(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::togleCenter()");
    #endif
    this->centerState = 255 - this->centerState;
    ledcWrite(this->centerChannel, this->centerState);
    this->updateTime = millis();
}

// **************
// *** MIDDLE ***
// **************
void Valves::setMiddleState(unsigned char state){
    #ifdef IN_DEBUG_MODE
        Serial.printf("\t\tValves::setMiddleState(%d)\n", state);
    #endif
    this->middleState = state;
    ledcWrite(this->middleChannel, state);
    this->updateTime = millis();
}

bool Valves::isMiddleOn(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::isMiddleOn()");
    #endif
    return this->middleState > MID_DUTY_CYCLE;
}

void Valves::turnOnMiddle(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOnMiddle()");
    #endif
    if (this->middleState == MAX_DUTY_CYCLE) return;
    this->middleState = MAX_DUTY_CYCLE;
    ledcWrite(this->middleChannel, MAX_DUTY_CYCLE);
    this->updateTime = millis();
}

void Valves::turnOffMiddle(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOffMiddle()");
    #endif
    if (this->middleState == MIN_DUTY_CYCLE) return;
    this->middleState = MIN_DUTY_CYCLE;
    ledcWrite(this->middleChannel, MIN_DUTY_CYCLE);
    this->updateTime = millis();
}

void Valves::togleMiddle(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::togleMiddle()");
    #endif
    this->middleState = 255 - this->middleState;
    ledcWrite(this->middleChannel, this->middleState);
    this->updateTime = millis();
}

// ****************
// *** EXTERNAL ***
// ****************
void Valves::setExternalState(unsigned char state){
    #ifdef IN_DEBUG_MODE
        Serial.printf("\t\tValves::setExternalState(%d)\n", state);
    #endif
    this->externalState = state;
    ledcWrite(this->externalChannel, state);
    this->updateTime = millis();
}

bool Valves::isExternalOn(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::isExternalOn()");
    #endif
    return this->externalState > MID_DUTY_CYCLE;
}

void Valves::turnOnExternal(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOnExternal()");
    #endif
    if (this->externalState == MAX_DUTY_CYCLE) return;
    this->externalState = MAX_DUTY_CYCLE;
    ledcWrite(this->externalChannel, MAX_DUTY_CYCLE);
    this->updateTime = millis();
}

void Valves::turnOffExternal(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOffExternal()");
    #endif
    if (this->externalState == MIN_DUTY_CYCLE) return;
    this->externalState = MIN_DUTY_CYCLE;
    ledcWrite(this->externalChannel, MIN_DUTY_CYCLE);
    this->updateTime = millis();
}

void Valves::togleExternal(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::togleExternal()");
    #endif
    this->externalState = 255 - this->externalState;
    ledcWrite(this->externalChannel, this->externalChannel);
    this->updateTime = millis();
}
