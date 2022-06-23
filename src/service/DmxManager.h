#ifndef __VALVE_H__
#define __VALVE_H__

#include <math.h>
#include <dmx/ESPDMX.h>

class DmxManager
{
    public:
        DmxManager (DMXESPSerial *dmx, Fountain *fountain);

        unsigned long getUpdateTime();
        unsigned char getState();

        void setState(unsigned char state);

    private:
        const int PWM_FREQ = 5000; /* 5 KHz */
        const unsigned char PWM_RESOLUTION = 8;
        const unsigned char MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1);
        const unsigned char MID_DUTY_CYCLE = MAX_DUTY_CYCLE / 2;
        const unsigned char MIN_DUTY_CYCLE = 0;

        unsigned long updateTime = 0;

        DMXESPSerial *dmx;

        unsigned char channel;
        unsigned char state = MIN_DUTY_CYCLE;

};

#endif