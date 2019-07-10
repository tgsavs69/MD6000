void setup() {

  Serial.begin(115200);
  for (int i = 22; i <= 34; i = i + 2) {
    pinMode(i, OUTPUT);
    pinMode(i + 1, INPUT_PULLUP);
  }

}

void loop() {

  for (int i = 23; i <= 35; i = i + 2) {
    Serial.print((i-21)/2);
    Serial.print(": ");
  Serial.print(digitalRead(i));
  Serial.print("  ");
    digitalWrite(i - 1, digitalRead(i));
  }
  Serial.println();
 

}
