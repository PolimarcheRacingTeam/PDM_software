#include <Voltage.h>

float Voltages::getVoltage(int pin, float voltageDividerRatio)
{
    return (analogRead(pin) * (M4_V_REF / M4_RESOLUTION)) * voltageDividerRatio;
}