#include <FastLED.h>

#define POWER_BUTTON_PIN 12
#define BUTTON_ONE_PIN 11
#define BUTTON_TWO_PIN 10
#define BUTTON_THREE_PIN 9
#define BUTTON_FOUR_PIN 8
#define BUTTON_FIVE_PIN 7
#define JOYSTICK_X_PIN 5
#define JOYSTICK_Y_PIN 4

unsigned long lastTime;

// void logButtons() {
//     Serial.print("POWER: ");
//     Serial.println(digitalRead(POWER_BUTTON_PIN) == HIGH ? "HIGH" : "LOW");
//     Serial.print("ONE: ");
//     Serial.println(digitalRead(BUTTON_ONE_PIN) == HIGH ? "HIGH" : "LOW");
//     Serial.print("TWO: ");
//     Serial.println(digitalRead(BUTTON_TWO_PIN) == HIGH ? "HIGH" : "LOW");
//     Serial.print("THREE: ");
//     Serial.println(digitalRead(BUTTON_THREE_PIN) == HIGH ? "HIGH" : "LOW");
//     Serial.print("FOUR: ");
//     Serial.println(digitalRead(BUTTON_FOUR_PIN) == HIGH ? "HIGH" : "LOW");
//     Serial.print("FIVE: ");
//     Serial.println(digitalRead(BUTTON_FIVE_PIN) == HIGH ? "HIGH" : "LOW");
//     Serial.println();
// }

void logJoystick() {

}

void setup() {
    lastTime = millis();
    // Serial.begin(9600);
    pinMode(POWER_BUTTON_PIN, INPUT_PULLUP);
    pinMode(BUTTON_ONE_PIN, INPUT_PULLUP);
    pinMode(BUTTON_TWO_PIN, INPUT_PULLUP);
    pinMode(BUTTON_THREE_PIN, INPUT_PULLUP);
    pinMode(BUTTON_FOUR_PIN, INPUT_PULLUP);
    pinMode(BUTTON_FIVE_PIN, INPUT_PULLUP);
}

void loop() {
    if (millis() - lastTime > 500) {
        lastTime = millis();
    }
}
