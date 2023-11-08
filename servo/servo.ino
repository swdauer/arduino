#include <Servo.h>
#define SERVO 9

Servo myServo;

void setup() {
    myServo.attach(SERVO);
    myServo.write(90);
    delay(500);
}

void loop() {
    myServo.write(180);
    delay(500);
    myServo.write(0);
    delay(1000);
    myServo.write(90);
    delay(500);
}