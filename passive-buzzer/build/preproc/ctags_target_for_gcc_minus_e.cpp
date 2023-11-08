# 1 "/home/swdauer/workspace/arduino/passive-buzzer/passive-buzzer.ino"
# 2 "/home/swdauer/workspace/arduino/passive-buzzer/passive-buzzer.ino" 2



void setup() {
    pinMode(13, 0x1);
    pinMode(4, 0x2);
    pinMode(11, 0x1);
}

void loop() {
    digitalWrite(13, 0x0);
    if (digitalRead(4) == 0x0) {
        unsigned int melody[] = { 262, 330, 392 };
        for (int i = 0; i < 3; i++) {
            tone(11, melody[i], 500);
            delay(1000);
        }
    }
}
