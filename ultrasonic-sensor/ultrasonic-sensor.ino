#include <HCSR04.h>

#define TRIGGER 12
#define ECHO 11

UltraSonicDistanceSensor distanceSensor(TRIGGER, ECHO);

void setup() {
    Serial.begin(9600);
}

void loop() {
    float distance = distanceSensor.measureDistanceCm();
    Serial.println(distance);
    delay(500);
}