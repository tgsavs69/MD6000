#include "keypadFile.h"
#include "lcdFile.h"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  startLCD();
}
bool readBloodPressureActivated = false;
void loop() {
  char key = keypad.getKey();

  if (key) {
      readBloodPressure(key);
  }

 
}
/*
void readBloodPressure() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Blood pressure:");

  lcd.setCursor(0, 1);
  lcd.print("Value:");



}*/
