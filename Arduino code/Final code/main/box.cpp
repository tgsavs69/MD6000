#include <Arduino.h>
#include "box.h"
#include "drawer.h"


box::box() {
  numberOfDrawers = 0;
}
box::box(int tempNumber, drawer* tempDrawer) {
  numberOfDrawers = tempNumber;

  if (list != NULL)
    delete [] list;

  list =  new drawer[numberOfDrawers];

  for (int i = 0; i < numberOfDrawers; i++) {
    list[i] = tempDrawer[i];
  }

}


void box::addDrawer(int tempNumber, int tempLed, int tempSwitch, int tempInterval = 0, int tempNumberOfPills = 0, int tempStartingHour = -1) {
  numberOfDrawers = numberOfDrawers + 1;

  drawer* tempArray = new drawer[numberOfDrawers];
  for (int i = 0; i < numberOfDrawers - 1; i++) {
    tempArray[i] = list[i];
  }

  drawer tempDrawer(tempNumber, tempLed, tempSwitch, tempInterval, tempNumberOfPills, tempStartingHour);
  tempArray[numberOfDrawers - 1] = tempDrawer;
  if (list != NULL) {
    delete[] list;
  }
  list = tempArray;

}

void box::displayBox() {
  for (int i = 0; i < numberOfDrawers; i++) {
    Serial.print("Drawer ");
    Serial.println(i + 1);
    Serial.println("-----------------------");
    list[i].displayDrawer();
    Serial.println();
  }
}



void box::addAlarm(int tempDrawer, int tempInterval, int tempNumberOfPills, int tempStartingHour) {
  list[tempDrawer].addAlarm(tempInterval, tempNumberOfPills, tempStartingHour);
}

void box::activate(int tempId) {
  /*
    if (tempId <= 0 || tempId > numberOfDrawers) {
    Serial.println("ID INVALID BOX::ACTIVATED");
    return -1;
    }
    list[tempId-1].activate();
  */

}
int box::activated(int tempID) {

  for (int i = 0; i < numberOfDrawers; i++) {
    if (list[i].getID() == tempID) {
      return list[i].activated();
    }
  }
  return -1;
  /*
    if (tempId <= 0 || tempId > numberOfDrawers) {
      Serial.println("ID INVALID BOX::ACTIVATED");
      return -1;
    }
    return list[tempId-1].activated();
  */
}


int box::getNumberPills(int tempID) {
  for (int i = 0; i < numberOfDrawers; i++) {
    if (list[i].getID() == tempID) {
      return list[i].getNumberPills();
    }
  }
  return -1;
}


int box::getStatusDrawer(int tempID) {
  for (int i = 0; i < numberOfDrawers; i++) {
    if (list[i].getID() == tempID) {
      return list[i].getStatus();
    }
  }
  return -1;
}


void box::alarmActivated(int *tempStateDrawers) {


  for (int i = 0; i < numberOfDrawers; i++) {
    tempStateDrawers[i] =  list[i].getStatus();
  }
}


drawer box::returnDrawer(int tempId) {
  for (int i = 0; i < numberOfDrawers; i++) {
    if (list[i].getID() == tempId) {
      return list[i];
    }
  }
}
