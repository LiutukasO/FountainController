#ifndef __VALVES_H__
#define __VALVES_H__

typedef struct valve_state {
  bool center;
  bool middle;
  bool external;
} valve_state;

class Valves
{
    public:
        Valves (unsigned char centerPin, unsigned char middlePin, unsigned char externalPin);

        unsigned long getUpdateTime();
        valve_state getState();

        bool isOnCenter();
        void turnOnCenter();
        void turnOffCenter();
        void togleCenter();

        bool isOnMiddle();
        void turnOnMiddle();
        void turnOffMiddle();
        void togleMiddle();

        bool isOnExternal();
        void turnOnExternal();
        void turnOffExternal();
        void togleExternal();

    private:
        unsigned long updateTime = 0;

        unsigned char centerPin;
        unsigned char middlePin;
        unsigned char externalPin;

};

#endif