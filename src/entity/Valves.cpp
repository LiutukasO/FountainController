#include <entity/Valves.h>
#include <Arduino.h>

//#define IN_DEBUG_MODE

Valves::Valves (DMXESPSerial *dmx, unsigned char channelGroup){
    this->dmx = dmx;

    this->centerChannel = channelGroup + 0;
    this->centerState = MIN_DUTY_CYCLE;
    this->dmx->write(this->centerChannel, this->centerState);
    Serial.printf("\n\t\tCenter valve channel: %d", this->centerChannel);

    this->ring1Channel = channelGroup + 1;
    this->ring1State = MIN_DUTY_CYCLE;
    this->dmx->write(this->ring1Channel, this->ring1State);
    Serial.printf("\n\t\tRing1 valve channel: %d", this->ring1Channel);

    this->ring2Channel = channelGroup + 2;
    this->ring2State = MIN_DUTY_CYCLE;
    this->dmx->write(this->ring2Channel, this->ring2State);
    Serial.printf("\n\t\tRing2 valve channel: %d", this->ring2Channel);

    this->ring3Channel = channelGroup + 3;
    this->ring3State = MIN_DUTY_CYCLE;
    this->dmx->write(this->ring3Channel, this->ring3State);
    Serial.printf("\n\t\tRing3 valve channel: %d", this->ring3Channel);

    this->dmx->update();
    this->updateTime = millis();
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
    valveState.center = this->centerState;
    valveState.ring1  = this->ring1State;
    valveState.ring2  = this->ring2State;
    valveState.ring3  = this->ring3State;
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
    this->dmx->write(this->centerChannel, this->centerState);
    this->dmx->update();
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
    this->dmx->write(this->centerChannel, this->centerState);
    this->dmx->update();
    this->updateTime = millis();
}

void Valves::turnOffCenter(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOffCenter()");
    #endif
    if (this->centerState == MIN_DUTY_CYCLE) return;
    this->centerState = MIN_DUTY_CYCLE;
    this->dmx->write(this->centerChannel, this->centerState);
    this->dmx->update();
    this->updateTime = millis();
}

void Valves::togleCenter(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::togleCenter()");
    #endif
    this->centerState = 255 - this->centerState;
    this->dmx->write(this->centerState, this->centerState);
    this->dmx->update();
    this->updateTime = millis();
}

// **************
// *** RING-1 ***
// **************
void Valves::setRing1State(unsigned char state){
    #ifdef IN_DEBUG_MODE
        Serial.printf("\t\tValves::setRing1State(%d)\n", state);
    #endif
    this->ring1State = state;
    this->dmx->write(this->ring1Channel, this->ring1State);
    this->dmx->update();
    this->updateTime = millis();
}

bool Valves::isRing1On(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::isRing1On()");
    #endif
    return this->ring1State > MID_DUTY_CYCLE;
}

void Valves::turnOnRing1(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOnRing1()");
    #endif
    if (this->ring1State == MAX_DUTY_CYCLE) return;
    this->ring1State = MAX_DUTY_CYCLE;
    this->dmx->write(this->ring1Channel, this->ring1State);
    this->dmx->update();
    this->updateTime = millis();
}

void Valves::turnOffRing1(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOffRing1()");
    #endif
    if (this->ring1State == MIN_DUTY_CYCLE) return;
    this->ring1State = MIN_DUTY_CYCLE;
    this->dmx->write(this->ring1Channel, this->ring1State);
    this->dmx->update();
    this->updateTime = millis();
}

void Valves::togleRing1(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::togleRing1()");
    #endif
    this->ring1State = 255 - this->ring1State;
    this->dmx->write(this->ring1Channel, this->ring1State);
    this->dmx->update();
    this->updateTime = millis();
}

// **************
// *** RING-2 ***
// **************
void Valves::setRing2State(unsigned char state){
    #ifdef IN_DEBUG_MODE
        Serial.printf("\t\tValves::setRing2State(%d)\n", state);
    #endif
    this->ring2State = state;
    this->dmx->write(this->ring2Channel, this->ring2State);
    this->dmx->update();
    this->updateTime = millis();
}

bool Valves::isRing2On(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::isRing2On()");
    #endif
    return this->ring2State > MID_DUTY_CYCLE;
}

void Valves::turnOnRing2(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOnRing2()");
    #endif
    if (this->ring2State == MAX_DUTY_CYCLE) return;
    this->ring2State = MAX_DUTY_CYCLE;
    this->dmx->write(this->ring2Channel, this->ring2State);
    this->dmx->update();
    this->updateTime = millis();
}

void Valves::turnOffRing2(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOffRing2()");
    #endif
    if (this->ring2State == MIN_DUTY_CYCLE) return;
    this->ring2State = MIN_DUTY_CYCLE;
    this->dmx->write(this->ring2Channel, this->ring2State);
    this->dmx->update();
    this->updateTime = millis();
}

void Valves::togleRing2(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::togleRing2()");
    #endif
    this->ring2State = 255 - this->ring2State;
    this->dmx->write(this->ring2Channel, this->ring2State);
    this->dmx->update();
    this->updateTime = millis();
}

// **************
// *** RING-3 ***
// **************
void Valves::setRing3State(unsigned char state){
    #ifdef IN_DEBUG_MODE
        Serial.printf("\t\tValves::setRing3State(%d)\n", state);
    #endif
    this->ring3State = state;
    this->dmx->write(this->ring3Channel, this->ring3State);
    this->dmx->update();
    this->updateTime = millis();
}

bool Valves::isRing3On(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::isRing3On()");
    #endif
    return this->ring3State > MID_DUTY_CYCLE;
}

void Valves::turnOnRing3(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOnRing3()");
    #endif
    if (this->ring3State == MAX_DUTY_CYCLE) return;
    this->ring3State = MAX_DUTY_CYCLE;
    this->dmx->write(this->ring3Channel, this->ring3State);
    this->dmx->update();
    this->updateTime = millis();
}

void Valves::turnOffRing3(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::turnOffRing3()");
    #endif
    if (this->ring3State == MIN_DUTY_CYCLE) return;
    this->ring3State = MIN_DUTY_CYCLE;
    this->dmx->write(this->ring3Channel, this->ring3State);
    this->dmx->update();
    this->updateTime = millis();
}

void Valves::togleRing3(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tValves::togleRing3()");
    #endif
    this->ring3State = 255 - this->ring3State;
    this->dmx->write(this->ring3Channel, this->ring3State);
    this->dmx->update();
    this->updateTime = millis();
}
