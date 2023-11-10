#include <RelayHandler.h>

void RelayHandler::setRelayState(bool state, int pin)
{
    if (state == 1)
    {
        digitalWrite(pin, HIGH);
    }
    else
    {
        digitalWrite(pin, LOW);
    }
}