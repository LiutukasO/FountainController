#include <entity/Led.h>
#include <Arduino.h>

//#define IN_DEBUG_MODE

Led::Led (DMXESPSerial *dmx, unsigned char channelGroup){
    this->dmx = dmx;

    this->redChannel = channelGroup + 0;
    this->redState = MIN_DUTY_CYCLE;
    this->dmx->write(this->redChannel, this->redState);

    this->greenChannel = channelGroup + 1;
    this->greenState = MIN_DUTY_CYCLE;
    this->dmx->write(this->greenChannel, this->greenState);

    this->blueChannel = channelGroup + 2;
    this->blueState = MIN_DUTY_CYCLE;
    this->dmx->write(this->blueChannel, this->blueState);

    this->dmx->update();
    this->updateTime = millis();
}

led_state Led::getState(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::getState()");
    #endif
    led_state ledState;
    ledState.red   = this->redState;
    ledState.green = this->greenState;
    ledState.blue  = this->blueState;
    return ledState;
}

//********************
//****** RED *********
//********************
void Led::setRedState(unsigned char state){
    #ifdef IN_DEBUG_MODE
        Serial.printf("\t\tLed::setRedState(%d)\n", state);
    #endif
    this->redState = state;
    this->dmx->write(this->redChannel, this->redState);
    this->dmx->update();
    this->updateTime = millis();
}

bool Led::isRedOn(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::isRedOn()");
    #endif
    return this->redState > MID_DUTY_CYCLE;
}

void Led::turnOnRed(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::turnOnRed()");
    #endif
    if (this->redState == MAX_DUTY_CYCLE) return;
    this->redState = MAX_DUTY_CYCLE;
    this->dmx->write(this->redChannel, this->redState);
    this->dmx->update();
    this->updateTime = millis();
}

void Led::turnOffRed(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::turnOffRed()");
    #endif
    if (this->redState == MIN_DUTY_CYCLE) return;
    this->redState = MIN_DUTY_CYCLE;
    this->dmx->write(this->redChannel, this->redState);
    this->dmx->update();
    this->updateTime = millis();
}

void Led::togleRed(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::togleRed()");
    #endif
    this->redState = 255 - this->redState;
    this->dmx->write(this->redChannel, this->redState);
    this->dmx->update();
    this->updateTime = millis();
}

//**********************
//****** GREEN *********
//**********************
void Led::setGreenState(unsigned char state){
    #ifdef IN_DEBUG_MODE
        Serial.printf("\t\tLed::setGreenState(%d)\n", state);
    #endif
    this->greenState = state;
    this->dmx->write(this->greenChannel, this->greenState);
    this->dmx->update();
    this->updateTime = millis();
}

bool Led::isGreenOn(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::isGreenOn()");
    #endif
    return this->greenState > MID_DUTY_CYCLE;
}

void Led::turnOnGreen(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::turnOnGreen()");
    #endif
    if (this->greenState == MAX_DUTY_CYCLE) return;
    this->greenState = MAX_DUTY_CYCLE;
    this->dmx->write(this->greenChannel, this->greenState);
    this->dmx->update();
    this->updateTime = millis();
}

void Led::turnOffGreen(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::turnOffGreen()");
    #endif
    if (this->greenState == MIN_DUTY_CYCLE) return;
    this->greenState = MIN_DUTY_CYCLE;
    this->dmx->write(this->greenChannel, this->greenState);
    this->dmx->update();
    this->updateTime = millis();
}

void Led::togleGreen(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::togleGreen()");
    #endif
    this->greenState = 255 - this->greenState;
    this->dmx->write(this->greenChannel, this->greenState);
    this->dmx->update();
    this->updateTime = millis();
}

//*********************
//****** BLUE *********
//*********************
void Led::setBlueState(unsigned char state){
    #ifdef IN_DEBUG_MODE
        Serial.printf("\t\tLed::setBlueState(%d)\n", state);
    #endif
    this->blueState = state;
    this->dmx->write(this->blueChannel, this->blueState);
    this->dmx->update();
    this->updateTime = millis();
}

bool Led::isBlueOn(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::isBlueOn()");
    #endif
    return this->blueState > MID_DUTY_CYCLE;
}

void Led::turnOnBlue(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::turnOnBlue()");
    #endif
    if (this->blueState == MAX_DUTY_CYCLE) return;
    this->blueState = MAX_DUTY_CYCLE;
    this->dmx->write(this->blueChannel, this->blueState);
    this->dmx->update();
    this->updateTime = millis();
}

void Led::turnOffBlue(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::turnOffBlue()");
    #endif
    if (this->blueState == MIN_DUTY_CYCLE) return;
    this->blueState = MIN_DUTY_CYCLE;
    this->dmx->write(this->blueChannel, this->blueState);
    this->dmx->update();
    this->updateTime = millis();
}

void Led::togleBlue(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::togleBlue()");
    #endif
    this->blueState = 255 - this->blueState;
    this->dmx->write(this->blueChannel, this->blueState);
    this->dmx->update();
    this->updateTime = millis();
}
