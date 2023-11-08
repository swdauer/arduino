#include "pitches.h"
#define BUTTON 4
#define BUZZER 11

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
