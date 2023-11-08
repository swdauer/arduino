// define pins
#define RED 3
#define GREEN 5
#define BLUE 6
#define LED_VAL_MAX 255

typedef struct rgb {
    int red;
    int green;
    int blue;
} rgb;

rgb ledValues = { 0, 0, 0 };

void setup() {
    pinMode(RED, OUTPUT);
    pinMode(BLUE, OUTPUT);
    pinMode(GREEN, OUTPUT);
    writeLed(ledValues);
}

void loop() {
#define DELAY 10

    for (int i = 0; i <= LED_VAL_MAX; i++) {
        changeLed(&ledValues, { 1, 0, 0 });
        delay(DELAY);
    }
    for (int i = 0; i <= LED_VAL_MAX; i++) {
        changeLed(&ledValues, { -1, 0, 0 });
        delay(DELAY);
    }

    for (int i = 0; i <= LED_VAL_MAX; i++) {
        changeLed(&ledValues, { 0, 1, 0 });
        delay(DELAY);
    }
    for (int i = 0; i <= LED_VAL_MAX; i++) {
        changeLed(&ledValues, { 0, -1, 0 });
        delay(DELAY);
    }

    for (int i = 0; i <= LED_VAL_MAX; i++) {
        changeLed(&ledValues, { 0, 0, 1 });
        delay(DELAY);
    }
    for (int i = 0; i <= LED_VAL_MAX; i++) {
        changeLed(&ledValues, { 0, 0, -1 });
        delay(DELAY);
    }
}

int constrictBetween0and255(int input) {
    if (input < 0) return 0;
    else if (input > LED_VAL_MAX) return LED_VAL_MAX;
    else return input;
}

// the leds are currently at values and will be changed by the change parameter.
// the values will contain the new values of the leds after the change.
void changeLed(rgb* values, rgb change) {
    values->red = constrictBetween0and255(values->red + change.red);
    values->green = constrictBetween0and255(values->green + change.green);
    values->blue = constrictBetween0and255(values->blue + change.blue);
    writeLed(*values);
}

void writeLed(const rgb values) {
    analogWrite(RED, values.red);
    analogWrite(GREEN, values.green);
    analogWrite(BLUE, values.blue);
}
