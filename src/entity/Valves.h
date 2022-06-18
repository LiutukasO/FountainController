#ifndef __VALVES_H__
#define __VALVES_H__

#include <math.h>
#include <dmx/ESPDMX.h>

typedef struct valve_state {
  unsigned char center;
  unsigned char ring1;
  unsigned char ring2;
  unsigned char ring3;
} valve_state;

class Valves
{
    public:
        Valves (DMXESPSerial *dmx, unsigned char channelGroup);

        unsigned long getUpdateTime();
        valve_state getState();

        void setCenterState(unsigned char state);
        bool isCenterOn();
        void turnOnCenter();
        void turnOffCenter();
        void togleCenter();

        void setRing1State(unsigned char state);
        bool isRing1On();
        void turnOnRing1();
        void turnOffRing1();
        void togleRing1();

        void setRing2State(unsigned char state);
        bool isRing2On();
        void turnOnRing2();
        void turnOffRing2();
        void togleRing2();

        void setRing3State(unsigned char state);
        bool isRing3On();
        void turnOnRing3();
        void turnOffRing3();
        void togleRing3();

    private:
        const int PWM_FREQ = 5000; /* 5 KHz */
        const unsigned char PWM_RESOLUTION = 8;
        const unsigned char MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1);
        const unsigned char MID_DUTY_CYCLE = MAX_DUTY_CYCLE / 2;
        const unsigned char MIN_DUTY_CYCLE = 0;

        unsigned long updateTime = 0;

        DMXESPSerial *dmx;

        unsigned char centerChannel;
        unsigned char centerState = MIN_DUTY_CYCLE;

        unsigned char ring1Channel;
        unsigned char ring1State = MIN_DUTY_CYCLE;

        unsigned char ring2Channel;
        unsigned char ring2State = MIN_DUTY_CYCLE;

        unsigned char ring3Channel;
        unsigned char ring3State = MIN_DUTY_CYCLE;

};

#endif