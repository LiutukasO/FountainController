#ifndef __VALVES_H__
#define __VALVES_H__

#include <math.h>

typedef struct valve_state {
  unsigned char center;
  unsigned char middle;
  unsigned char external;
} valve_state;

class Valves
{
    public:
        Valves (unsigned char channelGroup, unsigned char centerPin, unsigned char middlePin, unsigned char externalPin);

        unsigned long getUpdateTime();
        valve_state getState();

        void setCenterState(unsigned char state);
        bool isCenterOn();
        void turnOnCenter();
        void turnOffCenter();
        void togleCenter();

        void setMiddleState(unsigned char state);
        bool isMiddleOn();
        void turnOnMiddle();
        void turnOffMiddle();
        void togleMiddle();

        void setExternalState(unsigned char state);
        bool isExternalOn();
        void turnOnExternal();
        void turnOffExternal();
        void togleExternal();

    private:
        const int PWM_FREQ = 5000; /* 5 KHz */
        const unsigned char PWM_RESOLUTION = 8;
        const unsigned char MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1);
        const unsigned char MID_DUTY_CYCLE = MAX_DUTY_CYCLE / 2;
        const unsigned char MIN_DUTY_CYCLE = 0;

        unsigned long updateTime = 0;

        unsigned char centerPin;
        unsigned char centerState = MIN_DUTY_CYCLE;
        unsigned char centerChannel;

        unsigned char middlePin;
        unsigned char middleState = MIN_DUTY_CYCLE;
        unsigned char middleChannel;

        unsigned char externalPin;
        unsigned char externalState = MIN_DUTY_CYCLE;
        unsigned char externalChannel;

};

#endif