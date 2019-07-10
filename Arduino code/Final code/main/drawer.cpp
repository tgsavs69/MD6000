#include <Arduino.h>
#include "drawer.h"

/* constructor without parameters */
drawer::drawer() {
}

/* constructor with all parameters */
drawer::drawer(int tempNumber, int tempLed, int tempSwitch, int tempInterval, int tempNumberOfPills, int tempStartingHour) {
  clone(tempNumber, tempLed, tempSwitch, tempInterval, tempNumberOfPills, tempStartingHour);
}

/* constructor without alarm parameters (interval, numberOfPills, startingHour */
drawer::drawer(int tempNumber, int tempLed, int tempSwitch) {
  clone(tempNumber, tempLed, tempSwitch);
}

drawer::drawer(const drawer& tempDrawer) {
  clone(tempDrawer.number, tempDrawer.pinLed, tempDrawer.pinSwitch, tempDrawer.timeBetweenPills, tempDrawer.numberOfPills, tempDrawer.startingHour);
}


drawer& drawer::operator=(const drawer& tempDrawer) {
  clone(tempDrawer.number, tempDrawer.pinLed, tempDrawer.pinSwitch, tempDrawer.timeBetweenPills, tempDrawer.numberOfPills, tempDrawer.startingHour);
}

void drawer::clone(int tempNumber, int tempLed, int tempSwitch, int tempInterval = 0, int tempNumberOfPills = 0, int tempStartingHour = 0) {
  number = tempNumber;

  pinLed = tempLed;
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, LOW);


  pinSwitch = tempSwitch;
  digitalWrite(pinSwitch, LOW);
  pinMode(pinSwitch, INPUT_PULLUP);



  timeBetweenPills = tempInterval; /*the period between taking pills */
  numberOfPills = tempNumberOfPills; /*how many pills to take once*/
  startingHour = tempStartingHour; /*when the alarm should be set up */

  alarmTriggered = 0;
}

void drawer::toggleLED(int state) {
  digitalWrite(pinLed, state);
}


void drawer::activate() {

  startingHour = startingHour + timeBetweenPills;
  if (startingHour > 23) startingHour = startingHour - 24;


  Serial.print("drawer::activate ->> Next alarm -> ");
  Serial.println(startingHour);


}

int drawer::activated() {
  int buttonState = digitalRead(pinSwitch);
  if (buttonState == LOW) {
    digitalWrite(pinLed, HIGH);
  }
  if (buttonState == HIGH) {
    digitalWrite(pinLed, LOW);
  }

  return buttonState;
}

void drawer::displayDrawer() {
  Serial.println();
  Serial.print("Number -> ");
  Serial.println(number);
  Serial.print("pinLed -> ");
  Serial.println(pinLed);
  Serial.print("pinSwitch -> ");
  Serial.println(pinSwitch);

  Serial.print("Interval -> ");
  Serial.print(timeBetweenPills);
  Serial.print(" numberOfPilss -> ");
  Serial.print(numberOfPills);
  Serial.print(" startingHour -> ");
  Serial.print(startingHour);
}

int drawer::returnNumber() {
  return number;
}

int drawer::returnPills() {
  return numberOfPills;
}


//add the alarm to the specific drawer
void drawer::addAlarm(int tempInterval, int tempNumberOfPills, int tempStartingHour) {
  timeBetweenPills = tempInterval;
  numberOfPills = tempNumberOfPills;
  startingHour = tempStartingHour;
  Serial.print(" -> startingHour = ");
  Serial.print(startingHour);
  Serial.print("    numberOfPills = ");
  Serial.print(numberOfPills);
  Serial.print("    interval = ");
  Serial.println(timeBetweenPills);
  delay(1000);

}


int drawer::statusDrawer() {
  int tempStatus = 0;
  if (hour() == startingHour && alarmTriggered == false) {
    tempStatus = 1; //the alarm is triggered
    digitalWrite(pinLed, HIGH);
    alarmTriggered = true;
  }
  if (minute() >= 30 && alarmTriggered == true) {
    tempStatus = 2; //alarm is triggered and the pill is not taken for 30 minutes
  }

  if(drawerOpen == 0 && digitalRead(pinSwitch) == 0){
    tempStatus = 3; // the drawer is opened
    drawerOpen = 1;
  }
  if (drawerOpen == 1 && alarmTriggered == true && digitalRead(pinSwitch) == 1) {
    tempStatus = 4; //tje pill is taken
    alarmTriggered = false;
  }


  return tempStatus;
  

  /*
    if (hour() == startingHour) {


    if(minute() >= 30)
    return 2;

    if (hour() == startingHour) {
    /*
    Serial.print("drawer::alarmActivated ->> ALARM ACTIVATED: Drawer ->");
    Serial.print(number);
    Serial.print("  Number of pills -> ");
    Serial.print(numberOfPills);
    Serial.print("  startingHour -> ");
    Serial.println(startingHour);
  */

}


//check if the drawer was open, then reset the alarmTriggered,
//and turn off the led
//  if (digitalRead(pinSwitch) == LOW && alarmTriggered == true) {
//    alarmTriggered = false;
//    digitalWrite(pinLed, LOW);
//}

// return 0;

/* if(alarmTriggered == true && minute() >= 30){
   Serial.println("ERROR");
    digitalWrite(pinLed,LOW);
    delay(100);
     digitalWrite(pinLed,HIGH);
     delay(100);
  }
*/


//}
