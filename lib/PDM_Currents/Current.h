#ifndef PDM_CURRENT_ACQUISITION
#define PDM_CURRENT_ACQUISITION

#include "MCP3008.h"

class Currents
{

private:
    const float BATTERY_SENSITIVITY = 0.04; // 40mV/A
    const float OTHERS_SENSITIVITIES = 0.2; // 200mV/A
    const float V_OFFSET = 0.5;             // 500mV
    typedef struct
    {
        int relayPin1;
        int relayPin2;
        int relayPin3;
        int relayPin4;
        int rail5VPin;
        int rail24VPin;
        int batteryPin;
    } PinMap;

    PinMap pinMap = {0, 1, 2, 3, 5, 4, 6};

public:
    float voltages[CHANNELS - 1];
    float currents[CHANNELS];
    Adafruit_MCP3008 mcp;
    void readVoltages();
    void toCurrents();
};

#endif