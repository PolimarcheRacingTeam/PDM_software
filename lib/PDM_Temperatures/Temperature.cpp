#include <Temperature.h>

Temperatures::Temperatures(int pin) : thermistorPin(pin) {}

// Calcolo della tensione di ingresso
// Calcolo della resistenza Vout = Vin*R2/ (R1+R2) ==> R1 = R2 *(1-Vout/Vin)
float Temperatures::getResistance()
{
    uint16_t adcValue = analogRead(thermistorPin);
    float voltage = adcValue * M4_V_REF / M4_RESOLUTION;
    return SERIES_RESISTOR * (M4_V_REF / voltage - 1.0);
}

float Temperatures::getTemperatures()
{
    float resistance = getResistance(), steinhart;
    steinhart = resistance / THERMISTOR_NOMINAL;       // (R/Ro)
    steinhart = log(steinhart);                        // ln(R/Ro)
    steinhart /= BCOEFFICIENT;                         // 1/B * ln(R/Ro)
    steinhart += 1.0 / (TEMPERATURE_NOMINAL + 298.15); // + (1/To)
    steinhart = 1.0 / steinhart;                       // Inverti
    return steinhart - 298.15;                         // Converti in °C
}