#ifndef __FONTAIN_MANAGER_H__
#define __FONTAIN_MANAGER_H__

#include <entity/Fountain.h>
#include <entity/AudioAnalyzer.h>

class FountainManager
{
    public:
        FountainManager (unsigned char audioPin);

        unsigned long getUpdateTime();
        bool isAudioConnected();
        fountain_state getFountainStateFromAudio();

        void audioConnect();
        void audioDisconnect();

        void valvesTurnOn();
        void valvesTurnOff();

        void ledsTurnOn();
        void ledsTurnOff();

    private:
        const unsigned int WATER_AUDIO_LEVEL_FROM =  10;
        const unsigned int RED_AUDIO_LEVEL_FROM   =   0;
        const unsigned int RED_AUDIO_LEVEL_TO     =  99;
        const unsigned int GREEN_AUDIO_LEVEL_FROM = 100;
        const unsigned int GREEN_AUDIO_LEVEL_TO   = 199;
        const unsigned int BLUE_AUDIO_LEVEL_FROM  = 200;
        const unsigned int BLUE_AUDIO_LEVEL_TO    = 299;

        unsigned long updateTime = 0;

        bool audioConnected = false;
        bool ledTurnedOn = true;
        bool valvesTurnedOn = true;

        AudioAnalyzer *audioAnalyzer;

        unsigned int getBossLevel  (audio_state audioState);
        unsigned int getMiddleLevel(audio_state audioState);
        unsigned int getTrebleLevel(audio_state audioState);
        bool isBetween(unsigned int value, unsigned int fromValue, unsigned int toValue);

};

#endif