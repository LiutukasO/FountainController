#ifndef __LED_H__
#define __LED_H__

typedef struct led_state {
  bool red;
  bool green;
  bool blue;
} led_state;

class Led
{
    public:
        Led (bool& needToFlush, unsigned char powerPin, unsigned char redPin, unsigned char greenPin, unsigned char bluePin);

        led_state getState();
        void flush();

        bool isRedOn();
        void turnOnRed();
        void turnOffRed();
        void togleRed();

        bool isGreenOn();
        void turnOnGreen();
        void turnOffGreen();
        void togleGreen();

        bool isBlueOn();
        void turnOnBlue();
        void turnOffBlue();
        void togleBlue();

    private:
        bool* needToFlush;
        unsigned long updateTime = 0;

        unsigned char powerPin;
        unsigned char redPin;
        unsigned char greenPin;
        unsigned char bluePin;

};

#endif