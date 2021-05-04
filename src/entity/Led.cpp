#include <entity/Led.h>
#include <Arduino.h>

//#define IN_DEBUG_MODE

Led::Led (bool& needToFlush, unsigned char powerPin, unsigned char redPin, unsigned char greenPin, unsigned char bluePin){
    this->needToFlush = &needToFlush;
    this->powerPin = powerPin;
    this->redPin = redPin;
    this->greenPin = greenPin;
    this->bluePin = bluePin;

    pinMode(this->powerPin, OUTPUT);
    pinMode(this->redPin, OUTPUT);
    pinMode(this->greenPin, OUTPUT);
    pinMode(this->bluePin, OUTPUT);
}

led_state Led::getState(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::getState()");
    #endif
    led_state ledState;
    ledState.red = digitalRead(redPin);
    ledState.green = digitalRead(greenPin);
    ledState.blue = digitalRead(bluePin);
    return ledState;
}

void Led::flush(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::flushStatus()");
    #endif
    if (!*this->needToFlush) return;
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tFlushing...");
    #endif
    digitalWrite(powerPin, HIGH);
    *this->needToFlush = false;
    delay(5);
    digitalWrite(powerPin, LOW);
}

//********************
//****** RED *********
//********************
bool Led::isRedOn(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::isRedOn()");
    #endif
    return digitalRead(this->redPin);
}

void Led::turnOnRed(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::turnOnRed()");
    #endif
    if (digitalRead(this->redPin) == HIGH) return;
    digitalWrite(redPin, HIGH);
    this->updateTime = millis();
}

void Led::turnOffRed(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::turnOffRed()");
    #endif
    if (digitalRead(this->redPin) == LOW) return;
    digitalWrite(redPin, LOW);
    this->updateTime = millis();
    *this->needToFlush = true;
}

void Led::togleRed(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::togleRed()");
    #endif
    if (digitalRead(this->redPin)){
        digitalWrite(redPin, LOW);
        *this->needToFlush = true;
    } else {
        digitalWrite(redPin, HIGH);
    }
    this->updateTime = millis();
}

//**********************
//****** GREEN *********
//**********************
bool Led::isGreenOn(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::isGreenOn()");
    #endif
    return digitalRead(this->greenPin);
}

void Led::turnOnGreen(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::turnOnGreen()");
    #endif
    if (digitalRead(this->greenPin) == HIGH) return;
    digitalWrite(greenPin, HIGH);
    this->updateTime = millis();
}

void Led::turnOffGreen(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::turnOffGreen()");
    #endif
    if (digitalRead(this->greenPin) == LOW) return;
    digitalWrite(greenPin, LOW);
    this->updateTime = millis();
    *this->needToFlush = true;
}

void Led::togleGreen(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::togleGreen()");
    #endif
    if (digitalRead(this->greenPin)){
        digitalWrite(greenPin, LOW);
        *this->needToFlush = true;
    } else {
        digitalWrite(greenPin, HIGH);
    }
    this->updateTime = millis();
}

//*********************
//****** BLUE *********
//*********************
bool Led::isBlueOn(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::isBlueOn()");
    #endif
    return digitalRead(this->bluePin);
}

void Led::turnOnBlue(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::turnOnBlue()");
    #endif
    if (digitalRead(this->bluePin) == HIGH) return;
    digitalWrite(bluePin, HIGH);
    this->updateTime = millis();
}

void Led::turnOffBlue(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::turnOffBlue()");
    #endif
    if (digitalRead(this->bluePin) == LOW) return;
    digitalWrite(bluePin, LOW);
    this->updateTime = millis();
    *this->needToFlush = true;
}

void Led::togleBlue(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tLed::togleBlue()");
    #endif
    if (digitalRead(this->bluePin)){
        digitalWrite(bluePin, LOW);
        *this->needToFlush = true;
    } else {
        digitalWrite(bluePin, HIGH);
    }
    this->updateTime = millis();
}
