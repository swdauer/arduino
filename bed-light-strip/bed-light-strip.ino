#include <FastLED.h>

#define POWER_BUTTON_PIN 12
#define BUTTON_ONE_PIN 11
#define BUTTON_TWO_PIN 10
#define BUTTON_THREE_PIN 9
#define BUTTON_FOUR_PIN 8
#define BUTTON_FIVE_PIN 7

#define JOYSTICK_X_PIN 5
#define JOYSTICK_Y_PIN 4

#define NUM_LEDS 300
#define LED_STRIP_PIN 2

unsigned long lastTime;
bool on = true;
CRGB leds[NUM_LEDS];
unsigned short currLed;


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

// void logJoystick() {
//     Serial.print("X: ");
//     Serial.println(analogRead(JOYSTICK_X_PIN));
//     Serial.print("Y: ");
//     Serial.println(analogRead(JOYSTICK_Y_PIN));
//     Serial.println();
// }

void clearLightStrip() {
    for (int i = 0; i < NUM_LEDS; i++) leds[i] = CRGB::Black;
    FastLED.show();
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
    FastLED.addLeds<NEOPIXEL, LED_STRIP_PIN>(leds, NUM_LEDS);
    clearLightStrip();
    currLed = 0;
}

void loop() {
    if (millis() - lastTime > 50) {
        leds[currLed] = CRGB::Purple;
        currLed++;
        FastLED.show();
        lastTime = millis();
    }
}
