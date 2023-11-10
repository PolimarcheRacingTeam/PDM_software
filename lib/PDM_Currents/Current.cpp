#include <Current.h>


// utilizziamo solo 7 canali di ingresso, quindi CHANNELS-1
// Legge le tensioni da tutti i canali e li memorizza in un array di tensioni
void Currents::readVoltages()
{
    for (int i = 0; i < CHANNELS - 1; i++)
    {
        voltages[i] = mcp.readADC(i) * (MCP_V_REF / MCP_RESOLUTION);
    }
}

/*
    Ciclo for per tutti i primi 5 canali.
    Converto le tensioni in corrente conoscendo la sensibilità e la tensione di offset dei sensori .
    Infine, calcolo la corrente della rail 12V per differenza e la corrente della batteria.

    Indicizzazione dell'array delle correnti:
    [0] -> relay 1
    [1] -> relay 2
    [2] -> relay 3
    [3] -> relay 4
    [4] -> rail 24V
    [5] -> rail 5V
    [6] -> rail 12V
    [7] -> batteria
  */
void Currents::toCurrents()
{
    for (int i = 0; i < CHANNELS - 2; i++)
    {
        // corrente dei primi 5 canali
        currents[i] = (voltages[i] - V_OFFSET) / OTHERS_SENSITIVITIES;
    }

    // corrente della rail 12V
    currents[CHANNELS - 2] = currents[pinMap.rail24VPin] - currents[pinMap.rail5VPin];
    // corrente della batteria
    currents[CHANNELS - 1] = voltages[pinMap.batteryPin] / BATTERY_SENSITIVITY;
}
