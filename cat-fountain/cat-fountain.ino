#define CON_BUT 4
#define LED 5
#define IR_DIST 1

// unsigned long time;
unsigned long lastOn;

void setup() {
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);

    pinMode(CON_BUT, INPUT);
    // Serial.begin(9600);
    // time = millis();
}

void loop() {
    if (digitalRead(CON_BUT) == HIGH) {
        digitalWrite(LED, HIGH);
    } else if (digitalRead(CON_BUT) == LOW) {
        digitalWrite(LED, LOW);
    }

    // if (millis() - time > 1000) {
    //     time = millis();
    //     Serial.println(analogRead(IR_DIST));
    // }
    // if (analogRead(IR_DIST) > 425) {
    //     digitalWrite(LED, HIGH);
    //     lastOn = millis();
    // } else if (millis() - lastOn > 5000) digitalWrite(LED, LOW);
}
