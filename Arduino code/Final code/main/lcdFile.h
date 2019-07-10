#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
String currentReading = "";
String mode[2] = {"SYSTOLIC", "DIASTOLIC"};
int currentMode = 0;
String systolicReading = "";
String diastolicReading = "";
void startLCD() {
  lcd.init();
  lcd.backlight();
}


boolean isReadingStarted = false;


void lcdPrintMessage(String lineA, String lineB) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(lineA);

  lcd.setCursor(0, 1);
  lcd.print(lineB);
}

void removeLastChar() {
  int lengthString = currentReading.length();
  if (lengthString > 0 && currentMode < 2) {
    currentReading.remove(lengthString - 1);
    lcdPrintMessage("BLOOD PRESSURE", mode[currentMode] + ":" + currentReading);
  }

}



void sendDataToESP() {
  Serial2.print("blood pressure ");
  if (systolicReading >= 0 && systolicReading <= 9) {
    Serial2.print("00");
  }
  if (systolicReading >= 10 && systolicReading <= 99) {
    Serial2.print("0");
  }
  Serial2.print(systolicReading);
  Serial2.print(" ");
  if (diastolicReading >= 0 && diastolicReading <= 9) {
    Serial2.print("00");
  }
  if (diastolicReading >= 10 && diastolicReading <= 99) {
    Serial2.print("0");
  }
  Serial2.print(diastolicReading);
  Serial2.print("#");


}

void changeMode() {
  Serial.print("current mode -> ");
  Serial.println(currentMode);

  switch (currentMode) {
    case 0:
      {

        int tempReading = currentReading.toInt();

        if (tempReading > 250) {

          currentReading = "";
          lcdPrintMessage("Invalid value", "Retype " + mode[currentMode]);
          delay(4000);
          lcdPrintMessage("BLOOD PRESSURE", mode[currentMode] + ":" + currentReading);
          return;
        }

        currentMode = 1;
        systolicReading = currentReading;
        currentReading = "";
        lcdPrintMessage("BLOOD PRESSURE", mode[currentMode] + ":" + currentReading);
        break;

      }
    case 1:
      {
        Serial.println("case 1 ");
        currentMode = 2;
        diastolicReading =  currentReading;//.toInt();
        long timeOut = millis();
        lcdPrintMessage("SYSTOLIC:" + systolicReading, "DIASTOLIC:" + diastolicReading);
        sendDataToESP();
        while ((millis() - timeOut < 5000) && !keypad.getKey());
        isReadingStarted = false;
        currentDisplayOption = 0;
        break;
      }
  }
  /*
    case 2:
    Serial.println("case 2 ");
    lcdPrintMessage("MD6000", "No messages");
    isReadingStarted = false;
    currentMode = 3;
    break;
  */
}





void readBloodPressure(char key) {
  if (isReadingStarted == false && key == '#') {
    currentMode = 0;
    currentReading = "";
    lcdPrintMessage("BLOOD PRESSURE", mode[currentMode] + ":");
    isReadingStarted = true;
    return;
  }
  if (isReadingStarted == true) {

    switch (key) {
      case '#': Serial.println(key); changeMode(); break;
      case '1': lcd.print("1"); currentReading += "1"; break;
      case '2': lcd.print("2"); currentReading += "2"; break;
      case '3': lcd.print("3"); currentReading += "3"; break;
      case '4': lcd.print("4"); currentReading += "4"; break;
      case '5': lcd.print("5"); currentReading += "5"; break;
      case '6': lcd.print("6"); currentReading += "6"; break;
      case '7': lcd.print("7"); currentReading += "7"; break;
      case '8': lcd.print("8"); currentReading += "8"; break;
      case '9': lcd.print("9"); currentReading += "9"; break;
      case '0': lcd.print("0"); currentReading += "0"; break;
      case '*': removeLastChar();  break;
    }
  }
}
