#ifndef __FONTAIN_H__
#define __FONTAIN_H__

#include <Arduino.h>
#include <dto/led/Led.h>
#include <dto/valve/Valve.h>>


typedef struct fountain_state {
  unsigned char valve;
  led_state led;
} fountain_state;


class Fountain
{
    public:
        Fountain (
              unsigned char valveChannel
            , unsigned char ledChannelGroup
        );

        Valve * getValve();
        Led * getLed();

        void setState(fountain_state fountainState);
        fountain_state getState();

        unsigned long getUpdateTime();

    private:
        unsigned long updateTime = 0;

        Valve *valve;
        Led *led;

        void updateValve(unsigned char valveState);
        void updateLed(led_state state);
};

#endif