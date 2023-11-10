#ifndef PDM_PWM_HANDLER
#define PDM_PWM_HANDLER

#include <Arduino.h>
#include <SAMD_PWM.h>

class PWMHandler
{
public:
    int NUM_OF_PINS = 5;
    void sendPWMSignal(float *dutyCycles, float *frequencies );

private:
    uint32_t PWM_Pins[5] = {0, 1, 4, 5, 6};
    SAMD_PWM* PWM_Instance[5];
};

#endif