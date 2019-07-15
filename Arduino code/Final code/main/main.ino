extern int currentDisplayOption = 0;

#include <Time.h>
#include <TimeAlarms.h>
#include <SoftwareSerial.h>
#include "drawer.h"
#include "box.h"
#include "DFRobotDFPlayerMini.h"

#include "keypadFile.h"
#include "lcdFile.h"


DFRobotDFPlayerMini myDFPlayer;


//create an empty drawer
box drawerPills;

//define the number of drawer
int numberOfDrawers = 6;
//define the pins used by the leds
int leds[]     = {/*drawer1*/ 38,/*drawer2*/ 30,/*drawer3*/ 28,/*drawer4*/ 26,/*drawer5*/ 24,/*drawer6*/ 22};
//define the pins used by the drawers
int switches[] = {/*drawer1*/ 39,/*drawer2*/ 31,/*drawer3*/ 29,/*drawer4*/ 27,/*drawer5*/ 25,/*drawer6*/ 23};



SoftwareSerial mySerial(8, 9);

drawer test;
int skipTime = A15;
void setup() {

  pinMode(skipTime, INPUT_PULLUP);


  Serial1.begin(9600);


  /*start the Serial communication with the computer*/
  Serial.begin(115200);
  if (!myDFPlayer.begin(Serial1)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  myDFPlayer.volume(20);  //Set volume value (0~30).


  startLCD();

  /*add 6 drawers to the drawer*/
  for (int i = 0; i < numberOfDrawers; i++) {
    drawerPills.addDrawer(/*id*/ i + 1,/*pinLed*/ leds[i],/*switchLed*/ switches[i], /*interval between pills*/ i + 1,/*numberOfPills*/ i + 1,/*startingHour*/ i + 1 );
  }

  /*display in Serial Monitor information about drawer*/
  drawerPills.displayBox();


  setTime(0, 0, 0, 1, 1, 11);


}

void makeAnnouncement() {
  myDFPlayer.playMp3Folder(0000);
  while (keypad.getKey() != '*') {
    if (myDFPlayer.available()) {
      if (myDFPlayer.readType() == DFPlayerPlayFinished) {
        Serial.println("Announcement finished");
        //break;
      }
    }
  }
}



void proccessDrawer(int idDrawer) {
  myDFPlayer.playMp3Folder(idDrawer);

  while (drawerPills.getStatusDrawer(idDrawer) == 1 || drawerPills.getStatusDrawer(idDrawer) == 2) {
    if (myDFPlayer.available()) {
      if (myDFPlayer.readType() == DFPlayerPlayFinished) {
        Serial.println("Open drawer announcement finished");
      }
    }
  }

  int numberOfPills = drawerPills.getNumberPills(idDrawer);
  myDFPlayer.playMp3Folder(10 + numberOfPills);
  while (drawerPills.getStatusDrawer(idDrawer) == 3) {
    if (myDFPlayer.available()) {
      if (myDFPlayer.readType() == DFPlayerPlayFinished) {
        Serial.println("Number of pills finished");
      }
    }

  }
  while (drawerPills.getStatusDrawer(idDrawer) == 4);
  while (drawerPills.getStatusDrawer(idDrawer) != 0);


}



bool readBloodPressureActivated = false;
bool keyboardEnabled = false;
int lastOption = -1;
bool onlyOnce = false;

bool announcement = false;



void loop() {

  char key = keypad.getKey();


  if (digitalRead(skipTime) == 0) {
    if (minute() + 20 > 60)
      setTime(hour() + 1, 0, second(), day(), month(), year());
    else {
      setTime(hour(), minute() + 20, second(), day(), month(), year());
    }
    digitalClockDisplay();
    delay(2000);
  }
  digitalClockDisplay();


  bool allPillsTaken = true;
  for (int i = 1; i <= numberOfDrawers; i++) {

    if (drawerPills.getStatusDrawer(i) != 0) {

      if (announcement == false) {
        announcement = true;
        makeAnnouncement();
      }
      allPillsTaken = false;
      proccessDrawer(i);
    }
  }

  if (allPillsTaken == true) {
    announcement = false;
  }

  if (currentDisplayOption != lastOption) {
    Serial.print("current option ->");
    Serial.println(currentDisplayOption);
    lastOption = currentDisplayOption;
    switch (currentDisplayOption) {
      case 0: lcdPrintMessage("MD6000",  "NO MESSAGES"); keyboardEnabled = false; break;
      case 1: lcdPrintMessage("MEASURE", "BLOOD PRESSURE"); keyboardEnabled = true; break;
        //  case 2: lcdPrintMessage("IT IS TIME", "TO TAKE YOUR MEDICINE");  takeMedicine(); break;



    }
    //lastOption = currentDisplayOption;
  }

  if (key) {
    switch (currentDisplayOption) {
      case 0: break;
      case 1: readBloodPressure(key); break;
    }

  }

  Alarm.delay(1000);
}



void digitalClockDisplay()
{
  lcd.setCursor(10, 0);
  // digital clock display of the time
  printDigits(hour());
  lcd.print(":");
  printDigits(minute());
  // printDigits(second());
  // Serial.println();
}

void printDigits(int digits)
{

  if (digits < 10)
    lcd.print('0');
  lcd.print(digits);
}
