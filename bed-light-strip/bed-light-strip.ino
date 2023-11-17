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

#define MAX_BRIGHTNESS 255

#define INPUT_DELAY 500 // milliseconds

unsigned long lastTime;
unsigned long lastOnStateChange;
unsigned long lastPaletteChange;
unsigned long lastBrightnessChange;
bool on = true;
CRGB leds[NUM_LEDS];
uint8_t currBrightness = 64;

#define NUM_PALETTES 8
CRGBPalette16 palettes[] = {
    CloudColors_p,
    LavaColors_p,
    OceanColors_p,
    ForestColors_p,
    RainbowColors_p,
    RainbowStripeColors_p,
    PartyColors_p,
    HeatColors_p
};
uint8_t currPaletteIndex = 0;


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
    lastPaletteChange = millis();
    lastBrightnessChange = millis();
    lastOnStateChange = millis();
    // Serial.begin(9600);
    pinMode(POWER_BUTTON_PIN, INPUT_PULLUP);
    pinMode(BUTTON_ONE_PIN, INPUT_PULLUP);
    pinMode(BUTTON_TWO_PIN, INPUT_PULLUP);
    pinMode(BUTTON_THREE_PIN, INPUT_PULLUP);
    pinMode(BUTTON_FOUR_PIN, INPUT_PULLUP);
    pinMode(BUTTON_FIVE_PIN, INPUT_PULLUP);
    FastLED.addLeds<NEOPIXEL, LED_STRIP_PIN>(leds, NUM_LEDS);
    fill_palette(leds, NUM_LEDS, 0, 1, palettes[currPaletteIndex], MAX_BRIGHTNESS, LINEARBLEND);
    FastLED.show();
}

/*
TODO: Fix on/off button
Make brightness changing via joystick have a longer time between each change
Use the max writes function from FastLED instead of a standard 50 millisecond delay for my outer if in loop()
Add custom palettes
Add custom function for displaying palettes in a wrapping fashion
Add animations
*/

void loop() {
    if (millis() - lastTime > 50) { // this delay is only for animations. there is a separate delay for inputs
        if (millis() > lastOnStateChange > INPUT_DELAY && digitalRead(POWER_BUTTON_PIN) == LOW) {
            on = !on;
            if (!on) clearLightStrip();
            else {
                fill_palette(leds, NUM_LEDS, 0, 1, palettes[currPaletteIndex], currBrightness, LINEARBLEND);
                FastLED.show();
            }
        }
    }
    if (on) {
        if (millis() - lastBrightnessChange > INPUT_DELAY && analogRead(JOYSTICK_X_PIN) > 800) {
            if (currBrightness > 255 - 16) currBrightness = 255;
            else currBrightness += 16;
            FastLED.setBrightness(currBrightness);
            FastLED.show();
        } else if (millis() - lastBrightnessChange > INPUT_DELAY && analogRead(JOYSTICK_X_PIN) < 200) {
            if (currBrightness < 16) currBrightness = 0;
            else currBrightness -= 16;
            FastLED.setBrightness(currBrightness);
            FastLED.show();
        }
        if (millis() - lastPaletteChange > INPUT_DELAY && analogRead(JOYSTICK_Y_PIN) > 800) {
            currPaletteIndex++;
            if (currPaletteIndex == NUM_PALETTES) currPaletteIndex = 0;
            fill_palette(leds, NUM_LEDS, 0, 1, palettes[currPaletteIndex], MAX_BRIGHTNESS, LINEARBLEND);
            FastLED.show();
            lastPaletteChange = millis();
        } else if (millis() - lastPaletteChange > INPUT_DELAY && analogRead(JOYSTICK_Y_PIN) < 200) {
            if (currPaletteIndex == 0) currPaletteIndex = NUM_PALETTES;
            currPaletteIndex--;
            fill_palette(leds, NUM_LEDS, 0, 1, palettes[currPaletteIndex], MAX_BRIGHTNESS, LINEARBLEND);
            FastLED.show();
            lastPaletteChange = millis();
        }
    }
    lastTime = millis();
}
