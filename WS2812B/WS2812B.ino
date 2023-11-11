#include <IRremote.h>
#include <FastLED.h>
#define NUM_LEDS 300
#define LED_PIN 6
#define IR_REMOTE 11
CRGB leds[NUM_LEDS];
bool on = true;
// short currLed = 0;

void setup() {
    Serial.begin(9600);
    IrReceiver.begin(IR_REMOTE, ENABLE_LED_FEEDBACK);
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
}

void loop() {
    if (IrReceiver.decode()) {
        Serial.println(IrReceiver.decodedIRData.command, HEX);
        if (IrReceiver.decodedIRData.command == 0x45) {
            on != on;
        }
        IrReceiver.resume(); // Enable receiving of the next value
    }
    // if (digitalRead(STOP_BUTTON_PIN) == HIGH) {
    //     leds[0] = CRGB::Black;
    // } else {
    //     leds[0] = CRGB::Purple;
    // }
    // FastLED.show();
    // delay(30);
    // if (!stop) {
    // } else {
    // }
}
