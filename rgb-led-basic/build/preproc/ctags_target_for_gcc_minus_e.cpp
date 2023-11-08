# 1 "/home/swdauer/workspace/arduino/rgb-led-basic/rgb-led-basic.ino"
// define pins





typedef struct rgb {
    int red;
    int green;
    int blue;
} rgb;

rgb ledValues = { 0, 0, 0 };

void setup() {
    pinMode(3, 0x1);
    pinMode(6, 0x1);
    pinMode(5, 0x1);
    writeLed(ledValues);
}

void loop() {


    for (int i = 0; i <= 255; i++) {
        changeLed(&ledValues, { 1, 0, 0 });
        delay(10);
    }
    for (int i = 0; i <= 255; i++) {
        changeLed(&ledValues, { -1, 0, 0 });
        delay(10);
    }

    for (int i = 0; i <= 255; i++) {
        changeLed(&ledValues, { 0, 1, 0 });
        delay(10);
    }
    for (int i = 0; i <= 255; i++) {
        changeLed(&ledValues, { 0, -1, 0 });
        delay(10);
    }

    for (int i = 0; i <= 255; i++) {
        changeLed(&ledValues, { 0, 0, 1 });
        delay(10);
    }
    for (int i = 0; i <= 255; i++) {
        changeLed(&ledValues, { 0, 0, -1 });
        delay(10);
    }
}

int constrictBetween0and255(int input) {
    if (input < 0) return 0;
    else if (input > 255) return 255;
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
    analogWrite(3, values.red);
    analogWrite(5, values.green);
    analogWrite(6, values.blue);
}
