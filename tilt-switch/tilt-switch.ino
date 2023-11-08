#define TILT_SWITCH 7

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(TILT_SWITCH, INPUT_PULLUP);
}

void loop() {
    if (digitalRead(TILT_SWITCH) == HIGH) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500); // for switch bounce
    } else {
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
    }
}