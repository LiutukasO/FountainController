#ifndef __FONTAIN_H__
#define __FONTAIN_H__

#include <Arduino.h>
#include <entity/Led.h>
#include <entity/Valves.h>
#include <dmx/ESPDMX.h>

typedef struct fountain_state {
  valve_state valveState;
  led_state led1State;
  led_state led2State;
  led_state led3State;
  led_state led4State;
} fountain_state;

class Fountain
{
    public:
        static void printValveState(valve_state valveState);
        static void printLedState(byte ledNo, led_state ledState);
        static void printFountainState(fountain_state fountainState);
        static String toJson(fountain_state fountainState);
        static led_state randomDemoLedState();
        static valve_state randomDemoValveState();
        static valve_state updateDemoValveState(valve_state valveState);
        static fountain_state getDemoFountainState(fountain_state fountainState);
        static fountain_state getDemoLedState(fountain_state fountainState);
        static fountain_state fadeLeds(fountain_state fountainState);
        Fountain (
              unsigned char valveChannelGroup
            , unsigned char led1ChannelGroup
            , unsigned char led2ChannelGroup
            , unsigned char led3ChannelGroup
            , unsigned char led4ChannelGroup
        );

        Valves * getValves();
        Led * getLed1();
        Led * getLed2();
        Led * getLed3();
        Led * getLed4();

        void initConnections();
        void showDemo();
        void updateState(fountain_state fountainState);
        unsigned long getUpdateTime();
        fountain_state getFountainState();

    private:
        unsigned long updateTime = 0;
        unsigned long fadeTime = 0;

        Valves *valves;
        Led *led1;
        Led *led2;
        Led *led3;
        Led *led4;

        DMXESPSerial dmx;

        void updateValves(valve_state fountainState);
        void updateLeds(Led *led, led_state fountainState);

};

#endif