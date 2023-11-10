/*
Acquisizione voltaggio dalle rail 5V, 12V e 24V
schema elettrico: https://imgur.com/a/zOqn3Xq

rail 5V:
  - R1 = 4.7kOhm
  - R2 = 4.7kOhm
  - 1/ratio = 2

rail 12V:
  - R3 = 8kOhm
  - R4 = 2kOhm
  - 1/ratio = 5

rail 24V:
  - R5 = 18kOhm
  - R6 = 2kOhm
  - 1/ratio = 10

*/

#ifndef PDM_VOLTAGE_ACQUISITION
#define PDM_VOLTAGE_ACQUISITION

#include <Arduino.h>
#include <Feather_M4_CAN.h>

class Voltages
{
private:
    const int TOT_CURRENTS = 3;

public:
    const float RATIO_5V = 2.0;
    const float RATIO_12V = 5.0;
    const float RATIO_24V = 10.0;
    const int PIN_5V = A2;
    const int PIN_12V = A3;
    const int PIN_24V = A4;
    float getVoltage(int pin, float voltageDividerRatio);
};

#endif