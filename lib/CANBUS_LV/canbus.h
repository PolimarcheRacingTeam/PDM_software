#ifndef CANBUS_h
#define CANBUS_h

#include <Arduino.h>

#define PIN_CAN_STANDBY (40)
#define PIN_CAN_BOOSTEN (41)

class CANBUS {
    public:
        void sendMessage(int address, const uint16_t* data, int dataLength, bool moreOneByte = true);
        void setupCAN();
    private:
        void intToBytes(const uint16_t* intArray, int arrayLength, uint8_t* byteArray, bool moreOneByte);
        bool checkArrayLenght(int dataLength, bool moreOneByte);
        void sendMoreOneByte(int address, const uint16_t* data, int dataLength);
        void sendOneByte(int address, const uint16_t* data, int dataLength);
        
};

void onReceive(int packetSize);
void bytesToInt(const uint8_t* byteArray, int arrayLength, uint16_t* intArray,bool moreOneByte);

#endif
