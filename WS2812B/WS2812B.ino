#include <FastLED.h>
#define NUM_LEDS 300
#define LED_PIN 6
#define JOYSTICK_X_PIN 0
#define JOYSTICK_Y_PIN 1
#define ON_BUTTON_PIN 4
CRGB leds[NUM_LEDS];
bool on = false;
unsigned long lastTime = 0;
unsigned short currLed = 0;

/*
TODO:
Devise on/off button
Perhaps add other buttons
Create separate class for bed lightstrip
Devise IO strategy with joystick and buttons
Hang lightstrip
*/

void clearLightStrip() {
    for (int i = 0; i < NUM_LEDS; i++) leds[i] = CRGB::Black;
    FastLED.show();
}

void setup() {
    lastTime = millis();
    pinMode(ON_BUTTON_PIN, INPUT_PULLUP);
    Serial.begin(115200);
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
    clearLightStrip();
    leds[0] = CRGB::Purple;
    FastLED.show();
}

void loop() {
    if (digitalRead(ON_BUTTON_PIN) == HIGH) on = true;
    else on = false;
    if (millis() - lastTime > 500) {
        Serial.println(analogRead(JOYSTICK_X_PIN));
        Serial.println(analogRead(JOYSTICK_Y_PIN));
        Serial.println();
        lastTime = millis();
    }
}
