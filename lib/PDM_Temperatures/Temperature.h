/*
  Software Mission:
  Leggere le temperature dei convertitori DC/DC montati sulla scheda PDM.
  Per la lettura è necessario andare a leggere la tensione sul partitore formato dal termistore NTC (871-B57702M0103J000)
  ed un resitore da 10kΩ.
  Convertire la misura di tensione nella temperatura in gradi celsius corrispondente.

  Schema elettrico: https://imgur.com/a/zBs5IZc

  Software Explanation:
  Utilizzo la formula di Stainhart-Hart per ottenere la relazione tra la temperatura e la resistenza:  1/T = A + B * ln(R/R0) + C * ln(R/R0)^3
  Per fortuna c'è un'equazione semplificata, la "B-parameter Equation": 1/T = 1/T0 + 1/B*ln(R/R0)
*/

#ifndef PDM_TEMPERATURE_ACQUISITION
#define PDM_TEMPERATURE_ACQUISITION

#include <math.h>
#include <NTC_871B57702M0103J000.h>
#include <Feather_M4_CAN.h>

class Temperatures
{
private:
    int thermistorPin;
    const float SERIES_RESISTOR = 10000.0; // Valore della resistenza in serie al termistore (ohm)
    float getResistance();

public:
    Temperatures(int pin = THERMISTOR_PIN); //THERMISTOR_PIN = A0
    float getTemperatures();
};

#endif