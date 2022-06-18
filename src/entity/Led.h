#ifndef __LED_H__
#define __LED_H__

#include <math.h>
#include <dmx/ESPDMX.h>

typedef struct led_state {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
} led_state;

class Led
{
    public:
        Led (DMXESPSerial *dmx, unsigned char channelGroup);

        led_state getState();

        void setRedState(unsigned char state);
        bool isRedOn();
        void turnOnRed();
        void turnOffRed();
        void togleRed();

        void setGreenState(unsigned char state);
        bool isGreenOn();
        void turnOnGreen();
        void turnOffGreen();
        void togleGreen();

        void setBlueState(unsigned char state);
        bool isBlueOn();
        void turnOnBlue();
        void turnOffBlue();
        void togleBlue();

    private:
        /* Setting PWM Properties */
        const int PWM_FREQ = 5000; /* 5 KHz */
        const unsigned char PWM_RESOLUTION = 8;
        const unsigned char MAX_DUTY_CYCLE = (unsigned char)(pow(2, PWM_RESOLUTION) - 1);
        const unsigned char MID_DUTY_CYCLE = MAX_DUTY_CYCLE / 2;
        const unsigned char MIN_DUTY_CYCLE = 0;

        unsigned long updateTime;

        DMXESPSerial *dmx;

        unsigned char redChannel;
        unsigned char redState;

        unsigned char greenChannel;
        unsigned char greenState;

        unsigned char blueChannel;
        unsigned char blueState;

};

#endif