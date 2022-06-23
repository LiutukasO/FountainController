#include <service/DmxManager.h>
#include <dto/fountain/Fountain.h>
#include <Arduino.h>

//#define IN_DEBUG_MODE

DmxManager::DmxManager (DMXESPSerial *dmx, Fountain *fountain){
    this->dmx = dmx;

    this->dmx->write(this->channel, this->state);
    Serial.printf("\n\t\tValve channel: %d", this->channel);

    this->dmx->update();
    this->updateTime = millis();
}

unsigned long DmxManager::getUpdateTime(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\t\tDmxManager::getUpdateTime()");
    #endif
    return this->updateTime;
}

void DmxManager::setState(unsigned char state){
    #ifdef IN_DEBUG_MODE
        Serial.printf("\t\tDmxManager::setState(%d)\n", state);
    #endif
    this->dmx->write(this->channel, this->state);
    this->dmx->update();
    this->updateTime = millis();
}
