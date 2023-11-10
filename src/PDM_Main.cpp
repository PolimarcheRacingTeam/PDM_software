#include <canbus.h>
#include <PWMHandler.h>
#include <Temperature.h>
#include <Current.h>
#include <Voltage.h>
#include <RelayHandler.h>

CANBUS can;
Currents currents;
Temperatures temperatures;
Voltages voltages;
RelayHandler relay;
PWMHandler pwm;

void setup() {
  can.setupCAN();
}

void loop() {
  // Esempio di invio sul CAN di 3 dati letti da un sensore
  uint16_t dataToSend[] = { 123, 260, 12 };
  int dataLength = sizeof(dataToSend) / sizeof(dataToSend[0]);
  can.sendMessage(0x10, dataToSend, dataLength);
  delay(5000);


  float temperature = temperatures.getTemperatures();
  if (temperature > 50) {
    // DO SOMETHING
  } else {
    // DO SOMETHING OTHERWISE
  }

  float voltage = voltages.getVoltage(voltages.PIN_24V, voltages.RATIO_24V);
  if (voltage > 3.3) {
    // DO SOMETHING
  } else {
    // DO SOMETHING OTHERWISE
  }

  currents.readVoltages();
  currents.toCurrents();
  // DO SOMETHING WITH THE ARRAY OF CURRENTS

  // Esempio di settaggio dello stato del relay al pin 10
  bool stateFromCan = 0;
  relay.setRelayState(stateFromCan, relay.PIN10);

  // Esempio di una generazione di diversi segnali PWM
  // in base ai parametri 'dutycycle' e alla 'frequenza'
  float dutyCyclesFromCAN[] = { 10.0f, 90.0f, 40.0f, 60.0f };
  float frequenciesFromCAN[] = { 100.0f, 200.0f, 50.0f, 75.0f };
  pwm.sendPWMSignal(dutyCyclesFromCAN, frequenciesFromCAN);

}
