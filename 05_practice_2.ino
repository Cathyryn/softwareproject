int ledPin = 7;

void setup() {
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, 0);
  delay(1000);
}

void loop() {
  for (int i = 0; i <= 5; i++) {
    digitalWrite(ledPin, 0);
    delay(100);
    digitalWrite(ledPin, 1);
    delay(100);
  }

  digitalWrite(ledPin, 1);

  while (1) {
  }
}
