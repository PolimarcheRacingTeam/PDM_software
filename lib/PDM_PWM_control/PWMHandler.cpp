#include <PWMHandler.h>

void PWMHandler::sendPWMSignal(float *dutyCycles, float *frequencies)
{
    for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    PWM_Instance[index] = new SAMD_PWM(PWM_Pins[index], frequencies[index], dutyCycles[index]);

    if (PWM_Instance[index])
    {
      PWM_Instance[index]->setPWM();
    }
  }
}