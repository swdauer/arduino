#define CON_BUT 4
#define LED 5


void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);

  pinMode(CON_BUT, INPUT);
}

void loop() {
  if (digitalRead(CON_BUT) == HIGH) {
    digitalWrite(LED, HIGH);
  } else if (digitalRead(CON_BUT) == LOW) {
    digitalWrite(LED, LOW);
  }
}
