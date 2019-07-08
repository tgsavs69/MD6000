void setup() {

  for (int i = 22; i <= 32; i = i + 2) {
    pinMode(i, OUTPUT);
    pinMode(i + 1, INPUT_PULLUP);
  }

}

void loop() {

  for (int i = 23; i < 33; i = i + 2) {

    digitalWrite(i - 1, digitalRead(i));
  }

}
