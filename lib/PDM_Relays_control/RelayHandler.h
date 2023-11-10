#ifndef PDM_RELAY_HANDLER
#define PDM_RELAY_HANDLER

#include <Arduino.h>

class RelayHandler
{
public:
    const int PIN5 = A5;    //Relay_OUT_Drive4
    const int PIN9 = 9;     //Relay_OUT_Drive3
    const int PIN10 = 10;    //Relay_OUT_Drive2
    const int PIN11 = 11;    //Relay_OUT_Drive1
    const int PIN12 = 12;    //Relay12_Connector
    const int PIN13 = 13;    //Relay24V
    void setRelayState(bool state, int pin);
};

#endif