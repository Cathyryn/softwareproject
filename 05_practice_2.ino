#define PIN_LED 7

unsigned int toggle = 0;

void setup() {
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  toggle = 1;
  digitalWrite(PIN_LED, toggle);
  delay(1000);

  for (int i = 0; i < 10; i++) {
    toggle = !toggle;
    digitalWrite(PIN_LED, toggle);
    delay(100);
  }

  toggle = 0;
  digitalWrite(PIN_LED, toggle);

  while (1) {
  }
}
