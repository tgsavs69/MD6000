int numberOfComponents = 6;
int ledPins[] = {38,30,28,26,24,22};
int switchPins[] = {39,31,29,27,25,23};


void setup() {

  Serial.begin(115200);
  for (int i = 0; i < numberOfComponents; i++) {
   
    pinMode(ledPins[i], OUTPUT);
    pinMode(switchPins[i], INPUT_PULLUP);
  }

}

void loop() {

  for (int i = 0; i < numberOfComponents; i++) {
  Serial.print("Pin: ");
  Serial.print(switchPins[i]);
  Serial.print("->");
  Serial.print(digitalRead(switchPins[i]));
  Serial.print(" ");

  
  digitalWrite(ledPins[i], digitalRead(switchPins[i]));
  }
  Serial.println();
 

}
