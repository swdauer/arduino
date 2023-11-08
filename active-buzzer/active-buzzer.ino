#define BUZZER 11
#define BUTTON 4

void setup() {
    pinMode(BUTTON, INPUT_PULLUP);
    pinMode(BUZZER, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(BUZZER, LOW);
}

void loop() {
    if (digitalRead(BUTTON) == LOW) {
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(BUZZER, HIGH);
    } else {
        digitalWrite(BUZZER, LOW);
        digitalWrite(LED_BUILTIN, LOW);
    }
}