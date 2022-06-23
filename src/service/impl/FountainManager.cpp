
#include <service/FountainManager.h>

//#define IN_DEBUG_MODE

FountainManager::FountainManager(unsigned char audioPin){
    this->audioAnalyzer = new AudioAnalyzer(audioPin);
    DMX::Initialize();
}

unsigned long FountainManager::getUpdateTime(){
    return this->updateTime;
}

bool FountainManager::isAudioConnected(){
    return this->audioConnected;
}

void FountainManager::audioConnect(){
    this->audioConnected = true;
}

void FountainManager::audioDisconnect(){
    this->audioConnected = false;
}

bool FountainManager::isDmxConnected(){
    return this->dmxConnected;
}

void FountainManager::dmxConnect(){
    this->dmxConnected = true;
}

void FountainManager::dmxDisconnect(){
    this->dmxConnected = false;
}

void FountainManager::valvesTurnOn(){
    this->valvesTurnedOn = true;
}

void FountainManager::valvesTurnOff(){
    this->valvesTurnedOn = false;
}

void FountainManager::ledsTurnOn(){
    this->ledTurnedOn = true;
}

void FountainManager::ledsTurnOff(){
    this->ledTurnedOn = false;
}


unsigned int FountainManager::getBossLevel(audio_state audioState){
    unsigned int level = audioState.channel_sub_0HZ_20HZ;
    if (audioState.channel_bass_20HZ_40HZ  > level) level = audioState.channel_bass_20HZ_40HZ;
    if (audioState.channel_bass_40HZ_80HZ  > level) level = audioState.channel_bass_40HZ_80HZ;
    if (audioState.channel_bass_80HZ_160HZ > level) level = audioState.channel_bass_80HZ_160HZ;
    return map(level, 0, 1023, 0, 255);
}

unsigned int FountainManager::getMiddleLevel(audio_state audioState){
    unsigned int level = audioState.channel_bass_80HZ_160HZ;
    if (audioState.channel_mid_160HZ_300HZ > level) level = audioState.channel_mid_160HZ_300HZ;
    if (audioState.channel_mid_300HZ_600HZ > level) level = audioState.channel_mid_300HZ_600HZ;
    if (audioState.channel_mid_600HZ_1kHZ  > level) level = audioState.channel_mid_600HZ_1kHZ;
    return map(level, 0, 1023, 0, 255);
}

unsigned int FountainManager::getHighLevel(audio_state audioState){
    unsigned int level = audioState.channel_mid_600HZ_1kHZ;
    if (audioState.channel_treble_1kHZ_3kHZ > level) level = audioState.channel_treble_1kHZ_3kHZ;
    if (audioState.channel_treble_3kHZ_5kHZ > level) level = audioState.channel_treble_3kHZ_5kHZ;
    return map(level, 0, 1023, 0, 255);
}

unsigned int FountainManager::getTrebleLevel(audio_state audioState){
    unsigned int level = audioState.channel_treble_3kHZ_5kHZ;
    if (audioState.channel_treble_5kHZ_10kHZ > level) level = audioState.channel_treble_5kHZ_10kHZ;
    if (audioState.channel_top_10kHZ_20kHZ   > level) level = audioState.channel_top_10kHZ_20kHZ;
    return map(level, 0, 1023, 0, 255);
}

bool FountainManager::isBetween(unsigned int value, unsigned int fromValue, unsigned int toValue){
    if (value < fromValue) return false;
    if (value > toValue) return false;
    return true;
}

fountain_state FountainManager::getFountainStateFromAudio(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\tFountainManager::getFountainStateFromAudio()");
    #endif

    audio_state audioState = this->audioAnalyzer->getAudioState();
    fountain_state fountainState;

    unsigned int bossLevel   = this->getBossLevel(audioState);
    unsigned int middleLevel = this->getMiddleLevel(audioState);
    unsigned int highLevel   = this->getHighLevel(audioState);
    unsigned int trebleLevel = this->getTrebleLevel(audioState);

    fountainState.valveState.center = bossLevel   > FountainManager::WATER_AUDIO_LEVEL_FROM ? 255 : 0;
    fountainState.valveState.ring1  = middleLevel > FountainManager::WATER_AUDIO_LEVEL_FROM ? 255 : 0;
    fountainState.valveState.ring2  = highLevel   > FountainManager::WATER_AUDIO_LEVEL_FROM ? 255 : 0;
    fountainState.valveState.ring3  = trebleLevel > FountainManager::WATER_AUDIO_LEVEL_FROM ? 255 : 0;

    if (fountainState.valveState.center){
        fountainState.valveState.center = this->valvesTurnedOn ? 255 : 0;
        if (this->ledTurnedOn){
            fountainState.led1State.red   = isBetween(bossLevel, FountainManager::RED_AUDIO_LEVEL_FROM,   FountainManager::RED_AUDIO_LEVEL_TO) ? 255 : 0;
            fountainState.led1State.green = isBetween(bossLevel, FountainManager::GREEN_AUDIO_LEVEL_FROM, FountainManager::GREEN_AUDIO_LEVEL_TO) ? 255 : 0;
            fountainState.led1State.blue  = isBetween(bossLevel, FountainManager::BLUE_AUDIO_LEVEL_FROM,  FountainManager::BLUE_AUDIO_LEVEL_TO) ? 255 : 0;
        }
    }

    if (fountainState.valveState.ring1){
        fountainState.valveState.ring1 = this->valvesTurnedOn ? 255 : 0;
        if (this->ledTurnedOn){
            fountainState.led2State.red   = isBetween(middleLevel, FountainManager::RED_AUDIO_LEVEL_FROM,   FountainManager::RED_AUDIO_LEVEL_TO) ? 255 : 0;
            fountainState.led2State.green = isBetween(middleLevel, FountainManager::GREEN_AUDIO_LEVEL_FROM, FountainManager::GREEN_AUDIO_LEVEL_TO) ? 255 : 0;
            fountainState.led2State.blue  = isBetween(middleLevel, FountainManager::BLUE_AUDIO_LEVEL_FROM,  FountainManager::BLUE_AUDIO_LEVEL_TO) ? 255 : 0;
        }
    }

    if (fountainState.valveState.ring2){
        fountainState.valveState.ring2 = this->valvesTurnedOn ? 255 : 0;
        if (this->ledTurnedOn){
            fountainState.led3State.red   = isBetween(trebleLevel, FountainManager::RED_AUDIO_LEVEL_FROM,   FountainManager::RED_AUDIO_LEVEL_TO) ? 255 : 0;
            fountainState.led3State.green = isBetween(trebleLevel, FountainManager::GREEN_AUDIO_LEVEL_FROM, FountainManager::GREEN_AUDIO_LEVEL_TO) ? 255 : 0;
            fountainState.led3State.blue  = isBetween(trebleLevel, FountainManager::BLUE_AUDIO_LEVEL_FROM,  FountainManager::BLUE_AUDIO_LEVEL_TO) ? 255 : 0;
        }
    }

    if (fountainState.valveState.ring3){
        fountainState.valveState.ring3 = this->valvesTurnedOn ? 255 : 0;
        if (this->ledTurnedOn){
            fountainState.led4State.red   = isBetween(trebleLevel, FountainManager::RED_AUDIO_LEVEL_FROM,   FountainManager::RED_AUDIO_LEVEL_TO) ? 255 : 0;
            fountainState.led4State.green = isBetween(trebleLevel, FountainManager::GREEN_AUDIO_LEVEL_FROM, FountainManager::GREEN_AUDIO_LEVEL_TO) ? 255 : 0;
            fountainState.led4State.blue  = isBetween(trebleLevel, FountainManager::BLUE_AUDIO_LEVEL_FROM,  FountainManager::BLUE_AUDIO_LEVEL_TO) ? 255 : 0;
        }
    }

    return fountainState;
}

fountain_state FountainManager::getFountainStateFromDMX(){
    #ifdef IN_DEBUG_MODE
        Serial.println("\tFountainManager::getFountainStateFromDMX()");
    #endif
    fountain_state fountainState;
    if (!DMX::IsHealthy()){
        #ifdef IN_DEBUG_MODE
            Serial.println("\t\tDMX::IsHealthy() == FALSE");
        #endif
        return fountainState;
    }
    fountainState.valveState.center   = DMX::Read(1);
    fountainState.led1State.red       = DMX::Read(2);
    fountainState.led1State.green     = DMX::Read(3);
    fountainState.led1State.blue      = DMX::Read(4);

    fountainState.valveState.ring1    = DMX::Read(17);
    fountainState.led2State.red       = DMX::Read(18);
    fountainState.led2State.green     = DMX::Read(19);
    fountainState.led2State.blue      = DMX::Read(20);

    fountainState.valveState.ring2    = DMX::Read(33);
    fountainState.led3State.red       = DMX::Read(34);
    fountainState.led3State.green     = DMX::Read(35);
    fountainState.led3State.blue      = DMX::Read(36);

    fountainState.valveState.ring3    = DMX::Read(49);
    fountainState.led4State.red       = DMX::Read(50);
    fountainState.led4State.green     = DMX::Read(51);
    fountainState.led4State.blue      = DMX::Read(52);

   return fountainState;
}