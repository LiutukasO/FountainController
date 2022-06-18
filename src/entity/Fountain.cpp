#include <entity/Fountain.h>

#define IN_DEBUG_MODE

Fountain::Fountain (
              unsigned char valveChannelGroup
            , unsigned char led1ChannelGroup
            , unsigned char led2ChannelGroup
            , unsigned char led3ChannelGroup
            , unsigned char led4ChannelGroup
){
    this->dmx.init();
    this->valves = new Valves(&this->dmx, valveChannelGroup);
    this->led1 = new Led(&this->dmx, led1ChannelGroup);
    this->led2 = new Led(&this->dmx, led2ChannelGroup);
    this->led3 = new Led(&this->dmx, led3ChannelGroup);
    this->led4 = new Led(&this->dmx, led4ChannelGroup);
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
        Serial.printf("\n\tvalves: %d %d %d %d\n", fountainState.valveState.center, fountainState.valveState.ring1, fountainState.valveState.ring2, fountainState.valveState.ring3);
        Serial.printf("\tled 1: %d %d %d\n", fountainState.led1State.red, fountainState.led1State.green, fountainState.led1State.blue);
        Serial.printf("\tled 2: %d %d %d\n", fountainState.led2State.red, fountainState.led2State.green, fountainState.led2State.blue);
        Serial.printf("\tled 3: %d %d %d\n", fountainState.led3State.red, fountainState.led3State.green, fountainState.led3State.blue);
        Serial.printf("\tled 4: %d %d %d\n", fountainState.led4State.red, fountainState.led4State.green, fountainState.led4State.blue);
    #endif
}

String Fountain::toJson(fountain_state fountainState){
    String json = "{";
    json.concat("\"valveState\": {");
        json.concat("\"center\": "); json.concat(fountainState.valveState.center); json.concat(",");
        json.concat("\"ring1\": "); json.concat(fountainState.valveState.ring1); json.concat(",");
        json.concat("\"ring2\": "); json.concat(fountainState.valveState.ring2); json.concat(",");
        json.concat("\"ring3\": "); json.concat(fountainState.valveState.ring3);
    json.concat("},");
    json.concat("\"led1State\": {");
        json.concat("\"red\": "); json.concat(fountainState.led1State.red); json.concat(",");
        json.concat("\"green\": "); json.concat(fountainState.led1State.green); json.concat(",");
        json.concat("\"blue\": "); json.concat(fountainState.led1State.blue);
    json.concat("},");
    json.concat("\"led2State\": {");
        json.concat("\"red\": "); json.concat(fountainState.led2State.red); json.concat(",");
        json.concat("\"green\": "); json.concat(fountainState.led2State.green); json.concat(",");
        json.concat("\"blue\": "); json.concat(fountainState.led2State.blue);
    json.concat("},");
    json.concat("\"led3State\": {");
        json.concat("\"red\": "); json.concat(fountainState.led3State.red); json.concat(",");
        json.concat("\"green\": "); json.concat(fountainState.led3State.green); json.concat(",");
        json.concat("\"blue\": "); json.concat(fountainState.led3State.blue);
    json.concat("},");
    json.concat("\"led4State\": {");
        json.concat("\"red\": "); json.concat(fountainState.led4State.red); json.concat(",");
        json.concat("\"green\": "); json.concat(fountainState.led4State.green); json.concat(",");
        json.concat("\"blue\": "); json.concat(fountainState.led4State.blue);
    json.concat("}}");
    return json;
}

unsigned char getRandomState(){
    return rand() % 2 * 255;
}

fountain_state Fountain::getDemoFountainState(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\tgetDemoFountainState()");
    #endif
    fountain_state fountainState;

    fountainState.valveState.center = rand() % 2 * 255;
    fountainState.valveState.ring1  = rand() % 2 * 255;
    fountainState.valveState.ring2  = rand() % 2 * 255;
    fountainState.valveState.ring3  = rand() % 2 * 255;
    if (!fountainState.valveState.ring1 && !fountainState.valveState.ring2 && !fountainState.valveState.ring3){
        fountainState.valveState.center = 255;
    }

    // ***** LEDs in CENTER
    if (fountainState.valveState.center){
      fountainState.led1State.red   = getRandomState();
      fountainState.led1State.green = getRandomState();
      fountainState.led1State.blue  = getRandomState();
      if (!fountainState.led1State.red && !fountainState.led1State.green && !fountainState.led1State.red){
        fountainState.led1State.red   = 255;
        fountainState.led1State.green = 255;
        fountainState.led1State.blue  = 255;
      }
    } else {
      fountainState.led1State.red   = 0;
      fountainState.led1State.green = 0;
      fountainState.led1State.blue  = 0;
    }

    // ***** LEDs in RING-2
    if (fountainState.valveState.ring1){
      fountainState.led2State.red   = getRandomState();
      fountainState.led2State.green = getRandomState();
      fountainState.led2State.blue  = getRandomState();
      if (!fountainState.led2State.red && !fountainState.led2State.green && !fountainState.led2State.red){
        fountainState.led2State.red   = 255;
        fountainState.led2State.green = 255;
        fountainState.led2State.blue  = 255;
      }
    } else {
        fountainState.led2State.red   = 0;
        fountainState.led2State.green = 0;
        fountainState.led2State.blue  = 0;
    }

    // ***** LEDs in RING-3
    if (fountainState.valveState.ring2){
      fountainState.led3State.red   = getRandomState();
      fountainState.led3State.green = getRandomState();
      fountainState.led3State.blue  = getRandomState();
      if (!fountainState.led3State.red && !fountainState.led3State.green && !fountainState.led3State.red){
        fountainState.led3State.red   = 255;
        fountainState.led3State.green = 255;
        fountainState.led3State.blue  = 255;
      }
    } else {
      fountainState.led3State.red   = 0;
      fountainState.led3State.green = 0;
      fountainState.led3State.blue  = 0;
    }

    // ***** LEDs in RING-3
    if (fountainState.valveState.ring3){
      fountainState.led4State.red   = getRandomState();
      fountainState.led4State.green = getRandomState();
      fountainState.led4State.blue  = getRandomState();
      if (!fountainState.led4State.red && !fountainState.led4State.green && !fountainState.led4State.red){
        fountainState.led4State.red   = 255;
        fountainState.led4State.green = 255;
        fountainState.led4State.blue  = 255;
      }
    } else {
      fountainState.led4State.red   = 0;
      fountainState.led4State.green = 0;
      fountainState.led4State.blue  = 0;
    }

    return fountainState;
}

fountain_state Fountain::fadeLeds(fountain_state fountainState){
    if (fountainState.led1State.red)   fountainState.led1State.red--;
    if (fountainState.led1State.green) fountainState.led1State.green--;
    if (fountainState.led1State.blue)  fountainState.led1State.blue--;

    if (fountainState.led2State.red)   fountainState.led2State.red--;
    if (fountainState.led2State.green) fountainState.led2State.green--;
    if (fountainState.led2State.blue)  fountainState.led2State.blue--;

    if (fountainState.led3State.red)   fountainState.led3State.red--;
    if (fountainState.led3State.green) fountainState.led3State.green--;
    if (fountainState.led3State.blue)  fountainState.led3State.blue--;

    if (fountainState.led4State.red)   fountainState.led4State.red--;
    if (fountainState.led4State.green) fountainState.led4State.green--;
    if (fountainState.led4State.blue)  fountainState.led4State.blue--;
    return fountainState;
}

void Fountain::showDemo(){
    #ifdef IN_DEBUG_MODE
        //Serial.println("\tFountain::showDemo()");
    #endif
    if (updateTime + 3000 > millis()) {
        return;
        if (fadeTime + 20 > millis()) {
            return;
        }
        fountain_state fountainState = this->fadeLeds(this->getFountainState());
        this->updateLeds(this->getLed1(), fountainState.led1State);
        this->updateLeds(this->getLed2(), fountainState.led2State);
        this->updateLeds(this->getLed3(), fountainState.led3State);
        this->updateLeds(this->getLed4(), fountainState.led4State);
        this->fadeTime = millis();
        return;
    }
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
    this->dmx.update();
    this->updateTime = millis();
}

void Fountain::updateValves(valve_state valveState){
    #ifdef IN_DEBUG_MODE
        Serial.print("\tValves Center: "); Serial.println(valveState.center, DEC);
        Serial.print("\tValves Ring-1: "); Serial.println(valveState.ring1, DEC);
        Serial.print("\tValves Ring-2: "); Serial.println(valveState.ring2, DEC);
        Serial.print("\tValves Ring-3: "); Serial.println(valveState.ring3, DEC);
    #endif
    Valves *valves = this->getValves();
    valves->setCenterState(valveState.center);
    valves->setRing1State(valveState.ring1);
    valves->setRing2State(valveState.ring2);
    valves->setRing3State(valveState.ring3);
}

void Fountain::updateLeds(Led *led, led_state ledState){
    #ifdef IN_DEBUG_MODE
        Serial.printf("\tLed: %d %d %d \n", ledState.red, ledState.green, ledState.blue);
    #endif
    led->setRedState(ledState.red);
    led->setGreenState(ledState.green);
    led->setBlueState(ledState.blue);
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
