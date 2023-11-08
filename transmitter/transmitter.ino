#include <SPI.h>

// Registers
#define TX_ADDR 0x10
#define RX_ADDR_P0 0x0A
#define CONFIG 0
// SPI commands
#define R_REGISTER(reg) ((reg) & 0x1F)
#define W_REGISTER(reg) (R_REGISTER((reg)) | (1 << 5))
#define NOP 0xFF
#define W_TX_PAYLOAD 0b10100000

// SPI settings
#define SPI_CLOCK 10000000
#define SPI_SETTINGS SPISettings(SPI_CLOCK, MSBFIRST, SPI_MODE0)
// Register vals
#define CONFIG_FOR_TRANSMISSION 0
#define ADDRESS 0xABC87690DF

#define CSN_PIN 10 // SPI chip select
#define CE_PIN 9 // chip enable
#define BUTTON_PIN 4


byte command(byte spicommand, byte* buffer, byte size) {
    SPI.beginTransaction(SPI_SETTINGS);
    digitalWrite(CSN_PIN, LOW);

    byte status = SPI.transfer(spicommand);
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

void initTransmitter(byte* buffer) {
    writeToBuffer(buffer, CONFIG_FOR_TRANSMISSION, 1);
    command(W_REGISTER(CONFIG), buffer, 1);

    writeToBuffer(buffer, ADDRESS, 5);
    command(W_REGISTER(TX_ADDR), buffer, 5);
    writeToBuffer(buffer, ADDRESS, 5);
    command(W_REGISTER(RX_ADDR_P0), buffer, 5);
}

void transmit() {
    digitalWrite(CE_PIN, HIGH);
    delayMicroseconds(15);
    digitalWrite(CE_PIN, LOW);
}

byte spibuffer[5]; // for SPI transmissions
bool loaded = false;
bool pressed = false;
byte count = 1;

void setup() {
    pinMode(CSN_PIN, OUTPUT);
    digitalWrite(CSN_PIN, HIGH);
    pinMode(CE_PIN, OUTPUT);
    digitalWrite(CE_PIN, LOW);
    pinMode(BUTTON_PIN, INPUT);

    SPI.begin();
    Serial.begin(9600);
    initTransmitter(spibuffer);
}

void loop() {
    if (loaded == false && pressed == false && digitalRead(BUTTON_PIN) == HIGH) {
        writeToBuffer(spibuffer, count++, 1);
        command(W_TX_PAYLOAD, spibuffer, 1);
        pressed = true;
        loaded = true;
        Serial.print("1 ");
        Serial.println(count, HEX);
    }
    if (pressed == true && digitalRead(BUTTON_PIN) == LOW) {
        pressed = false;
        Serial.println("2");
    }
    if (loaded == true && pressed == false && digitalRead(BUTTON_PIN) == HIGH) {
        transmit();
        loaded = false;
        pressed = true;
        Serial.println("3");
    }
}
