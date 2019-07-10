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
int leds[]     = {/*drawer1*/ 34,/*drawer2*/ 30,/*drawer3*/ 28,/*drawer4*/ 26,/*drawer5*/ 24,/*drawer6*/ 22};
//define the pins used by the drawers
int switches[] = {/*drawer1*/ 35,/*drawer2*/ 31,/*drawer3*/ 29,/*drawer4*/ 27,/*drawer5*/ 25,/*drawer6*/ 23};



SoftwareSerial mySerial(8, 9);

drawer test;
void setup() {

  /*start the serial communication with the ESP8266*/
  mySerial.begin(115200);
  //esp serial
  //Serial2.begin(9600);
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
  myDFPlayer.volume(10);  //Set volume value (0~30).


  startLCD();

  /*add 6 drawers to the drawer*/
  for (int i = 0; i < numberOfDrawers; i++) {
    drawerPills.addDrawer(/*id*/ i + 1,/*pinLed*/ leds[i],/*switchLed*/ switches[i], i + 1, i + 1, i + 1 );
  }

  /*display in Serial Monitor information about drawer*/
  drawerPills.displayBox();


  // Serial.print("dimension -> ");
  //Serial.println(sizeof(drawerPills));
  setTime(23, 59, 55, 1, 1, 11);

  /*
    Serial.println();
    Serial.println("Waiting to receive data");

    int dataReceived = 0;
    while (dataReceived == 0) {
      Serial.write('z');
      if (mySerial.available()) {
        char c = mySerial.read();
        switch (c) {
          case 'a' : Serial.println("Starting to receive"); receiveData(); dataReceived = 1; break;

        }
      }
    }

    Serial.println("Setup finished");

    drawerPills.displayBox();
  */
}
/*
  void takeMedicine() {

  myDFPlayer.playMp3Folder(0000);

  while (keypad.getKey() != '*') {
    if (myDFPlayer.available()) {
      if (myDFPlayer.readType() == DFPlayerPlayFinished) {
        Serial.println("Announcement finished");
        //break;
      }
    }
  }


  while (drawerPills.alarmActivated() != 0) {

    int tempDrawer = drawerPills.alarmActivated();



    myDFPlayer.playMp3Folder(tempDrawer);
    while (drawerPills.returnDrawer(tempDrawer).activated()) {

      if (myDFPlayer.available()) {
        if (myDFPlayer.readType() == DFPlayerPlayFinished) {
          Serial.println("Open drawer announcement finished");
        }
      }
    }



    int numberOfPills = drawerPills.returnDrawer(tempDrawer).returnPills();
    myDFPlayer.playMp3Folder(10 + numberOfPills);
    Serial.print("main::takeMedicine -> numberOfPills = ");
    Serial.println(numberOfPills);
    while (drawerPills.returnDrawer(tempDrawer).activated() == 0) {
      drawerPills.activate(tempDrawer);
      break;
    }


    while (drawerPills.returnDrawer(tempDrawer).activated() == 0);


  }
  currentDisplayOption = 0;
  }
*/

void receiveData() {
  //reply to the transmitter to send data
  mySerial.write('k');

  //wait until the transmitter send data
  while (!mySerial.available());

  //wait for the whole data to be received
  delay(1000);

  int a = 0, b = 0, c = 0;
  for (int i = 0; i < 6; i++) {

    a = mySerial.parseInt();
    //drawers[i].startingHour = mySerial.parseInt();;
    //delay(100);
    b = mySerial.parseInt();
    //drawers[i].numberOfPills = mySerial.parseInt();;
    // delay(100);
    c = mySerial.parseInt();
    //drawers[i].interval = mySerial.parseInt();;
    // delay(100);
    /*
      Serial.print(i);
      Serial.print(" -> startingHour = ");
      Serial.print(a);
      Serial.print("    numberOfPills = ");
      Serial.print(b);
      Serial.print("    interval = ");
      Serial.println(c);
    */
    drawerPills.addAlarm(i, c, b, a);
    //delay(1000);
  }
  if (mySerial.read() == 'x')
    Serial.println("drawers received");
}


bool readBloodPressureActivated = false;
bool keyboardEnabled = false;
int lastOption = -1;
bool onlyOnce = false;


void loop() {

  char key = keypad.getKey();
  if (mySerial.available()) {
    char c = mySerial.read();
    switch (c) {
      case 'a' : Serial.println("Starting to receive"); receiveData(); break;

    }
  }

  if (second() == 20 && minute() < 30) {
    setTime(hour(), 29, 55, 1, 1, 11);
  }

  if (second() == 20 && minute() > 30) {
    setTime(hour(), 59, 55, 1, 1, 11);
  }



  digitalClockDisplay();

  int stateDrawers[6];
  drawerPills.alarmActivated(stateDrawers);
  Serial.println("State of drawers");
  for (int i = 0; i < numberOfDrawers; i++) {
    Serial.print(" Drawer ");
    Serial.print(i);
    Serial.print(" -> ");
    Serial.print(stateDrawers[i]);
  }
  Serial.println();
  /*
    if ( drawerPills.alarmActivated() != 0) {
      Serial.println("Setting currentDisplayOption = 2");
      currentDisplayOption = 2;
    }
  */

  /*
    if ( drawerPills.alarmActivated() != 0) {
      int tempDrawer = drawerPills.alarmActivated();
      myDFPlayer.playMp3Folder(0000);
      lcdPrintMessage("IT IS TIME", "TO TAKE MEDICINE");



      while (keypad.getKey() != '*') {
        if (myDFPlayer.available()) {
          if (myDFPlayer.readType() == DFPlayerPlayFinished) {
            Serial.println("Announcement finished");
            //break;
          }
        }
      }

      myDFPlayer.playMp3Folder(0001);
      while (true) {

        if (myDFPlayer.available()) {
          if (myDFPlayer.readType() == DFPlayerPlayFinished) {
            break;
          }
        }
      }
      myDFPlayer.playMp3Folder(11);
      Serial.print("Drawer :");
      Serial.println(tempDrawer);
      while (drawerPills.returnDrawer(tempDrawer).activated() == 1) {
        Serial.println(drawerPills.returnDrawer(tempDrawer).activated());
        delay(500);
      }

      lcdPrintMessage("MEDICINE", "WAS TAKEN");

      while (true);



    }
  */

  if (currentDisplayOption != lastOption) {
    Serial.print("current option ->");
    Serial.println(currentDisplayOption);
    lastOption = currentDisplayOption;
    switch (currentDisplayOption) {
      case 0: lcdPrintMessage("MD6000", "NO MESSAGES"); keyboardEnabled = false; break;
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
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}

void printDigits(int digits)
{
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
