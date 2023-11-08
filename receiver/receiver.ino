#include <SPI.h>

// Registers
#define TX_ADDR 0x10
#define RX_ADDR_P0 0x0A
#define RX_ADDR_P1 0x0B
#define RX_PW_P1 0x12
#define CONFIG 0
#define STATUS 0x7
// SPI commands
#define R_REGISTER(reg) ((reg) & 0x1F)
#define W_REGISTER(reg) (R_REGISTER((reg)) | (0x1 << 5))
#define NOP 0xFF
#define W_TX_PAYLOAD 0b10100000
#define R_RX_PAYLOAD 0b01100001

// SPI settings
#define SPI_CLOCK 10000000
#define SPI_SETTINGS SPISettings(SPI_CLOCK, MSBFIRST, SPI_MODE0)
// Register vals
#define CONFIG_FOR_RECEIVE 1
#define ADDRESS 0xABC87690DF

#define CSN_PIN 10 // SPI chip select
#define CE_PIN 9 // chip enable
// #define LED_PIN 4 


byte command(byte spicommand, byte* buffer, byte size) {
    SPI.beginTransaction(SPI_SETTINGS);
    digitalWrite(CSN_PIN, LOW);

    byte status = SPI.transfer(spicommand);
    if (size > 0)
        SPI.transfer(buffer, size);

    digitalWrite(CSN_PIN, HIGH);
    SPI.endTransaction();

    return status;
}

void writeToBuffer(byte* buffer, unsigned long long value, byte size) {
    unsigned long mask = 0xFF;
    for (int i = 0; i < size; i++) {
        buffer[i] = (value >> ((size - i - 1) * 8)) & mask;
    }
}

void initReceiver(byte* buffer) {
    writeToBuffer(buffer, CONFIG_FOR_RECEIVE, 1);
    command(W_REGISTER(CONFIG), buffer, 1);

    writeToBuffer(buffer, ADDRESS, 5);
    command(W_REGISTER(RX_ADDR_P1), buffer, 5);

    writeToBuffer(buffer, 1, 1);
    command(W_REGISTER(RX_PW_P1), buffer, 1);
}

bool checkForPacket(byte* buffer) {
    byte status = command(NOP, NULL, 0);
    // Serial.println(status, HEX);
    if (status & 0x40) {
        writeToBuffer(buffer, status & 0x40, 1);
        command(W_REGISTER(STATUS), buffer, 1);
        return true;
    }
    return false;
}

byte spibuffer[5]; // for SPI transmissions
unsigned long time;

void setup() {
    pinMode(CSN_PIN, OUTPUT);
    digitalWrite(CSN_PIN, HIGH);
    pinMode(CE_PIN, OUTPUT);
    digitalWrite(CE_PIN, LOW);
    // pinMode(LED_PIN, OUTPUT);
    // digitalWrite(LED_PIN, LOW);

    SPI.begin();
    Serial.begin(9600);
    initReceiver(spibuffer);
    digitalWrite(CE_PIN, HIGH);
    time = millis();
}

void loop() {
    if (millis() - time > 1000) {
        // if (checkForPacket(spibuffer)) {
        digitalWrite(CE_PIN, LOW);
        command(R_RX_PAYLOAD, spibuffer, 1);
        digitalWrite(CE_PIN, HIGH);
        // Serial.println(spibuffer[0], HEX);
        //      Serial.println("incheckif");
        // }
        command(R_REGISTER(RX_ADDR_P1), spibuffer, 5);
        for (int i = 0; i < 5; i++) Serial.print(spibuffer[i], HEX);
        Serial.println();
        time = millis();
        Serial.println("inmillisif");
    }
}
