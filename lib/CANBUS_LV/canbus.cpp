#include "canbus.h"
#include <CANSAME5x.h>

CANSAME5x CAN;

void CANBUS::setupCAN()
{
    pinMode(PIN_CAN_STANDBY, OUTPUT);
    digitalWrite(PIN_CAN_STANDBY, false); // disattivo la modalità STANDBY
    pinMode(PIN_CAN_BOOSTEN, OUTPUT);
    digitalWrite(PIN_CAN_BOOSTEN, true); // accendo la modalità booster

    if (!CAN.begin(500E3))
    {
        Serial.println("Inizializzazione CAN fallita!");
        while (1)
            delay(10);
    }

    CAN.onReceive(onReceive);
}

// Funzione che converte un array di interi in un array di byte
void CANBUS::intToBytes(const uint16_t *intArray, int arrayLength, uint8_t *byteArray, bool moreOneByte)
{
    if (moreOneByte)
    {
        for (int i = 0; i < arrayLength; i++)
        {
            byteArray[i * 2] = intArray[i] & 0xFF;
            byteArray[i * 2 + 1] = (intArray[i] >> 8) & 0xFF;
        }
    }
    else
    {
        for (int i = 0; i < arrayLength; i++)
        {
            byteArray[i] = intArray[i] & 0xFF;
        }
    }
}

void bytesToInt(const byte *byteArray, int arrayLength, uint16_t *intArray, bool moreOneByte)
{
    if (moreOneByte)
    {
        for (int i = 0; i < arrayLength; i++)
        {
            intArray[i] = (byteArray[i * 2 + 1] << 8) | byteArray[i * 2];
        }
    }
    else
    {
        for (int i = 0; i < arrayLength; i++)
        {
            intArray[i] = byteArray[i];
        }
    }
}

bool CANBUS::checkArrayLenght(int dataLength, bool moreOneByte)
{
    if (moreOneByte && dataLength > 4)
    {
        Serial.println("Errore: array di interi con più di 4 elementi.");
        return false;
    }
    else
    {
        if (!moreOneByte && dataLength > 8)
        {
            Serial.println("Errore: array di interi con più di 8 elementi.");
            return false;
        }
    }
    return true;
}

void CANBUS::sendMessage(int address, const uint16_t *data, int dataLength, bool moreOneByte)
{
    if (!checkArrayLenght(dataLength, moreOneByte))
    {
        return;
    }

    if (moreOneByte)
    {
        sendMoreOneByte(address, data, dataLength);
    }
    else
    {
        sendOneByte(address, data, dataLength);
    }
}

// Funzione che invia un messaggio con elementi che occupano più byte
void CANBUS::sendMoreOneByte(int address, const uint16_t *data, int dataLength)
{
    uint8_t byteArray[dataLength * 2];

    intToBytes(data, dataLength, byteArray, true);
    Serial.print("Indirizzo: 0x");
    Serial.println(address, HEX);
    Serial.println("Lunghezza: " + String(dataLength * 2) + " byte");
    Serial.print("Spedisco decimali: ");
    for (int i = 0; i < dataLength; i++)
    {
        Serial.print(data[i]);
        Serial.print(" ");
    }
    Serial.println();
    Serial.print("Equivalente in esadecimale:");
    for (int i = 0; i < dataLength * 2; i++)
    {
        if (i % 2 == 0)
        {
            Serial.print("| ");
        }
        Serial.print(byteArray[i], HEX);
        Serial.print(" ");
    }
    Serial.println("| ");

    CAN.beginPacket(address);
    for (int i = 0; i < dataLength * 2; ++i)
    {
        CAN.write(byteArray[i]);
    }
    CAN.endPacket();
}

// Funzione che invia un messaggio con elementi che occupano un solo byte
void CANBUS::sendOneByte(int address, const uint16_t *data, int dataLength)
{
    uint8_t byteArray[dataLength];

    intToBytes(data, dataLength, byteArray, false);
    Serial.print("Indirizzo: 0x");
    Serial.println(address, HEX);
    Serial.println("Lunghezza: " + String(dataLength) + " byte");
    Serial.print("Spedisco decimali: ");

    for (int i = 0; i < dataLength; i++)
    {
        Serial.print(data[i]);
        Serial.print(" ");
    }
    Serial.println();
    Serial.print("Equivalente in esadecimale:");
    Serial.print("| ");
    for (size_t i = 0; i < dataLength; i++)
    {
        Serial.print(byteArray[i], HEX);
        Serial.print(" | ");
    }
    Serial.println();

    CAN.beginPacket(address);
    for (int i = 0; i < dataLength; ++i)
    {
        CAN.write(byteArray[i]);
    }
    CAN.endPacket();
}

// Funzione che viene chiamata quando viene ricevuto un messaggio
void onReceive(int packetSize)
{
    uint8_t receivedBytes[packetSize];
    bool hasMoreThanOneByte = packetSize % 2 == 0;

    // determino la dimensione dell'array di interi
    // se la dimensione del pacchetto è pari, allora l'array di interi avrà metà elementi (ogni elemento è composto da 2 byte)
    // se la dimensione del pacchetto è dispari, allora l'array di interi avrà tanti elementi quanti i byte del pacchetto (ogni elemento è composto da 1 byte)
    int intArraySize;

    if (packetSize % 2 == 0)
    {
        intArraySize = packetSize / 2;
    }
    else
    {
        intArraySize = packetSize;
    }

    uint16_t intArray[intArraySize];

    // ho ricevuto un messaggio
    Serial.print("Ricevuto il pacchetto dall'indirizzo 0x");
    Serial.println(CAN.packetId(), HEX);
    Serial.print("Lunghezza: ");
    Serial.print(packetSize);
    Serial.println(" byte");

    // il messaggio è..
    Serial.print("Messaggio in esadecimale: ");
    Serial.print("| ");
    for (int i = 0; i < packetSize; i++)
    {
        uint8_t receivedByte = CAN.read();
        receivedBytes[i] = receivedByte; // Memorizza il byte letto nell'array
        Serial.print(receivedByte, HEX);
        Serial.print(" ");
        if (i % 2 == 0)
            Serial.print("| ");
    }
    Serial.println();

    bytesToInt(receivedBytes, intArraySize, intArray, hasMoreThanOneByte);

    Serial.print("Equivalente in decimale: ");
    for (size_t i = 0; i < intArraySize; i++)
    {
        Serial.print(intArray[i]);
        Serial.print(" ");
    }
    Serial.println("\n");
}
