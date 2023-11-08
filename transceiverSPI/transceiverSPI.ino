#include <SPI.h>

// SPI settings
#define SPI_CLOCK 10000000
#define SPI_SETTINGS SPISettings(SPI_CLOCK, MSBFIRST, SPI_MODE0)
// Registers
#define TX_ADDR 0x10
// SPI commands
#define R_REGISTER(reg) ((reg) & 0x1F)
#define W_REGISTER(reg) (R_REGISTER((reg)) | (0x1 << 5))
#define NOP 0xFF

#define CSN_PIN 10 // SPI chip select
#define CE_PIN 9 // chip enable

byte command(byte spicommand, byte* buffer, byte bufferSize) {
    SPI.beginTransaction(SPI_SETTINGS);
    digitalWrite(CSN_PIN, LOW);

    byte status = SPI.transfer(spicommand);
    SPI.transfer(buffer, bufferSize);

    digitalWrite(CSN_PIN, HIGH);
    SPI.endTransaction();

    return status;
}

byte buffer[5];

void setup() {
    pinMode(CSN_PIN, OUTPUT);
    digitalWrite(CSN_PIN, HIGH);

    SPI.begin();
    Serial.begin(9600);

    buffer[0] = 0x69;
    buffer[1] = 0x12;
    buffer[2] = 0xFF;
    buffer[3] = 0xAB;
    buffer[4] = 0x7C;
    command(W_REGISTER(TX_ADDR), buffer, 5);

}

void loop() {
    for (int i = 0; i < 5; i++) buffer[i] = NOP;
    command(R_REGISTER(TX_ADDR), buffer, 5);
    for (int i = 0; i < 5; i++) Serial.println(buffer[i], HEX);
    Serial.println("q\n");
    delay(1000);
}
