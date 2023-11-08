#include <Arduino.h>
#line 1 "/home/swdauer/workspace/arduino/passive-buzzer/passive-buzzer.ino"
#include "pitches.h"
#define BUTTON 4
#define BUZZER 11

#line 5 "/home/swdauer/workspace/arduino/passive-buzzer/passive-buzzer.ino"
void setup();
#line 11 "/home/swdauer/workspace/arduino/passive-buzzer/passive-buzzer.ino"
void loop();
#line 5 "/home/swdauer/workspace/arduino/passive-buzzer/passive-buzzer.ino"
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(BUTTON, INPUT_PULLUP);
    pinMode(BUZZER, OUTPUT);
}

void loop() {
    digitalWrite(LED_BUILTIN, LOW);
    if (digitalRead(BUTTON) == LOW) {
        unsigned int melody[] = { NOTE_C4, NOTE_E4, NOTE_G4 };
        for (int i = 0; i < 3; i++) {
            tone(BUZZER, melody[i], 500);
            delay(1000);
        }
    }
}

