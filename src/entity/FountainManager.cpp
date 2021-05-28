
#include <entity/FountainManager.h>


FountainManager::FountainManager(unsigned char audioPin){
    this->audioAnalyzer = new AudioAnalyzer(audioPin);
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
    return level;
}

unsigned int FountainManager::getMiddleLevel(audio_state audioState){
    unsigned int level = audioState.channel_treble_1kHZ_3kHZ;
    if (audioState.channel_mid_160HZ_300HZ > level) level = audioState.channel_mid_160HZ_300HZ;
    if (audioState.channel_mid_300HZ_600HZ > level) level = audioState.channel_mid_300HZ_600HZ;
    if (audioState.channel_mid_600HZ_1kHZ  > level) level = audioState.channel_mid_600HZ_1kHZ;
    return level;
}

unsigned int FountainManager::getTrebleLevel(audio_state audioState){
    unsigned int level = audioState.channel_treble_1kHZ_3kHZ;
    if (audioState.channel_treble_3kHZ_5kHZ  > level) level = audioState.channel_treble_3kHZ_5kHZ;
    if (audioState.channel_treble_5kHZ_10kHZ > level) level = audioState.channel_treble_5kHZ_10kHZ;
    if (audioState.channel_top_10kHZ_20kHZ   > level) level = audioState.channel_top_10kHZ_20kHZ;
    return level;
}

bool FountainManager::isBetween(unsigned int value, unsigned int fromValue, unsigned int toValue){
    if (value < fromValue) return false;
    if (value > toValue) return false;
    return true;
}

fountain_state FountainManager::getFountainStateFromAudio(){

    audio_state audioState = this->audioAnalyzer->getAudioState();
    fountain_state fountainState;

    unsigned int bossLevel   = this->getBossLevel(audioState);
    unsigned int middleLevel = this->getMiddleLevel(audioState);
    unsigned int trebleLevel = this->getTrebleLevel(audioState);

    fountainState.valveState.center   = bossLevel   > FountainManager::WATER_AUDIO_LEVEL_FROM ? 255 : 0;
    fountainState.valveState.middle   = middleLevel > FountainManager::WATER_AUDIO_LEVEL_FROM ? 255 : 0;
    fountainState.valveState.external = trebleLevel > FountainManager::WATER_AUDIO_LEVEL_FROM ? 255 : 0;

    if (fountainState.valveState.center){
        fountainState.valveState.center = this->valvesTurnedOn ? 255 : 0;
        if (this->ledTurnedOn){
            fountainState.led1State.red   = isBetween(bossLevel, FountainManager::RED_AUDIO_LEVEL_FROM,   FountainManager::RED_AUDIO_LEVEL_TO) ? 255 : 0;
            fountainState.led1State.green = isBetween(bossLevel, FountainManager::GREEN_AUDIO_LEVEL_FROM, FountainManager::GREEN_AUDIO_LEVEL_TO) ? 255 : 0;
            fountainState.led1State.blue  = isBetween(bossLevel, FountainManager::BLUE_AUDIO_LEVEL_FROM,  FountainManager::BLUE_AUDIO_LEVEL_TO) ? 255 : 0;
        }
    }

    if (fountainState.valveState.middle){
        fountainState.valveState.middle = this->valvesTurnedOn ? 255 : 0;
        if (this->ledTurnedOn){
            fountainState.led2State.red   = isBetween(middleLevel, FountainManager::RED_AUDIO_LEVEL_FROM,   FountainManager::RED_AUDIO_LEVEL_TO) ? 255 : 0;
            fountainState.led2State.green = isBetween(middleLevel, FountainManager::GREEN_AUDIO_LEVEL_FROM, FountainManager::GREEN_AUDIO_LEVEL_TO) ? 255 : 0;
            fountainState.led2State.blue  = isBetween(middleLevel, FountainManager::BLUE_AUDIO_LEVEL_FROM,  FountainManager::BLUE_AUDIO_LEVEL_TO) ? 255 : 0;
        }
    }

    if (fountainState.valveState.external){
        fountainState.valveState.external = this->valvesTurnedOn ? 255 : 0;
        if (this->ledTurnedOn){
            fountainState.led3State.red   = isBetween(trebleLevel, FountainManager::RED_AUDIO_LEVEL_FROM,   FountainManager::RED_AUDIO_LEVEL_TO) ? 255 : 0;
            fountainState.led3State.green = isBetween(trebleLevel, FountainManager::GREEN_AUDIO_LEVEL_FROM, FountainManager::GREEN_AUDIO_LEVEL_TO) ? 255 : 0;
            fountainState.led3State.blue  = isBetween(trebleLevel, FountainManager::BLUE_AUDIO_LEVEL_FROM,  FountainManager::BLUE_AUDIO_LEVEL_TO) ? 255 : 0;
            
            fountainState.led4State.red   = fountainState.led3State.red;
            fountainState.led4State.green = fountainState.led3State.green;
            fountainState.led4State.blue  = fountainState.led3State.blue;
        }
    }

    return fountainState;
}