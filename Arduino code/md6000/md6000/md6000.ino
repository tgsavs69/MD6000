extern int currentDisplayOption = 0;
#include "keypadFile.h"
#include "lcdFile.h"

long timer = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
  startLCD();

  timer = millis();
}
bool readBloodPressureActivated = false;
bool keyboardEnabled = false;
int lastOption = -1;
bool onlyOnce = false;
void loop() {

  char key = keypad.getKey();
  //Serial.println(millis() - timer);
  /*
    if ( (millis() - timer > 10000 ) && (currentDisplayOption == 0)  && onlyOnce == false) {
    currentDisplayOption = 1;
    timer = millis();

    onlyOnce = true;
    }
  */
  if (currentDisplayOption != lastOption) {
    Serial.print("current option ->");
    Serial.println(currentDisplayOption);
    switch (currentDisplayOption) {
      case 0: lcdPrintMessage("MD6000", "NO MESSAGES"); keyboardEnabled = false; break;
      case 1: lcdPrintMessage("MEASURE", "BLOOD PRESSURE"); keyboardEnabled = true; break;

    }
    lastOption = currentDisplayOption;
  }


  if (key) {
    switch (currentDisplayOption) {
      case 0: break;
      case 1: readBloodPressure(key); break;
    }

  }

  
  if (Serial2.available()) {
    delay(100);
    String message = "";
    char c = Serial2.read();
    long timeout = millis();
    
    while (c != '#' && millis() - timeout < 3000) {
      message += c;
      c = Serial2.read();
      delay(10);
    }
     Serial.println(message);
    if (message == "measure pressure") {
     currentDisplayOption = 1;
     Serial.println("Message received");
    }
    
    


  }



}
