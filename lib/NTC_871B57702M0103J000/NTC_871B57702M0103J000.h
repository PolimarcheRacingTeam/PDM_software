#ifndef NTC_871B57702M0103J000
#define NTC_871B57702M0103J000

#include <Adafruit_MCP3008.h>

const int THERMISTOR_PIN = A0;
const float THERMISTOR_NOMINAL = 10000.0;   // Valore nominale del termistore (ohm)
const float TEMPERATURE_NOMINAL = 25.0;      // Temperatura nominale del termistore (°C)
const float BCOEFFICIENT = 3950.0;          // Valore del coefficiente B del termistore

#endif
