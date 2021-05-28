#include <entity/Led.h>
#include <Arduino.h>

//#define IN_DEBUG_MODE

Led::Led (unsigned char channelGroup, unsigned char redPin, unsigned char greenPin, unsigned char bluePin){
    this->redPin = redPin;
    this->redChannel = channelGroup + 1;
    this->redState = MIN_DUTY_CYCLE;
    ledcAttachPin(this->redPin, this->redChannel);
    ledcSetup(this->redChannel, PWM_FREQ, this->redState);

    this->greenPin = greenPin;
    this->greenChannel = channelGroup + 2;
    this->greenState = MIN_DUTY_CYCLE;
    ledcAttachPin(this->greenPin, this->greenChannel);
    ledcSetup(this->greenChannel, PWM_FREQ, this->greenState);

    this->bluePin = bluePin;
    this->blueChannel = channelGroup + 3;
    this->blueState = MIN_DUTY_CYCLE;
    ledcAttachPin(this->bluePin, this->blueChannel);
    ledcSetup(this->blueChannel, PWM_FREQ, this->blueState);

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
    ledcWrite(this->redChannel, state);
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
    ledcWrite(this->redChannel, MAX_DUTY_CYCLE);
    this->updateTime = millis();
}

void Led::turnOffRed(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::turnOffRed()");
    #endif
    if (this->redState == MIN_DUTY_CYCLE) return;
    this->redState = MIN_DUTY_CYCLE;
    ledcWrite(this->redChannel, MIN_DUTY_CYCLE);
    this->updateTime = millis();
}

void Led::togleRed(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::togleRed()");
    #endif
    this->redState = 255 - this->redState;
    ledcWrite(this->redChannel, this->redState);
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
    ledcWrite(this->greenChannel, state);
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
    ledcWrite(this->greenChannel, MAX_DUTY_CYCLE);
    this->updateTime = millis();
}

void Led::turnOffGreen(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::turnOffGreen()");
    #endif
    if (this->greenState == MIN_DUTY_CYCLE) return;
    this->greenState = MIN_DUTY_CYCLE;
    ledcWrite(this->greenChannel, MIN_DUTY_CYCLE);
    this->updateTime = millis();
}

void Led::togleGreen(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::togleGreen()");
    #endif
    this->greenState = 255 - this->greenState;
    ledcWrite(this->greenChannel, this->greenState);
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
    ledcWrite(this->blueChannel, state);
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
    ledcWrite(this->blueChannel, MAX_DUTY_CYCLE);
    this->updateTime = millis();
}

void Led::turnOffBlue(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::turnOffBlue()");
    #endif
    if (this->blueState == MIN_DUTY_CYCLE) return;
    this->blueState = MIN_DUTY_CYCLE;
    ledcWrite(this->blueChannel, MIN_DUTY_CYCLE);
    this->updateTime = millis();
}

void Led::togleBlue(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::togleBlue()");
    #endif
    this->blueState = 255 - this->blueState;
    ledcWrite(this->blueChannel, this->blueState);
    this->updateTime = millis();
}
