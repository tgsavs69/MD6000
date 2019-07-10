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
  for (int i = 0; i < numberOfDrawers; i++) {
    if (list[i].returnNumber() == tempId) {
      list[i].activate();
      return;
    }
  }
}
void box::activated() {
  for (int i = 0; i < numberOfDrawers; i++) {
    list[i].activated();
  }
}

void box::alarmActivated(int *tempStateDrawers) {


  for (int i = 0; i < numberOfDrawers; i++) {
    tempStateDrawers[i] =  list[i].statusDrawer();
    /*
        tempStateDrawers[i] = 0;
        if ( list[i].alarmActivated() != 0) {
          tempStateDrawers[i] = 1;
          //return list[i].returnNumber();
        }
      }
    */


  }
}


  drawer box::returnDrawer(int tempId) {
    for (int i = 0; i < numberOfDrawers; i++) {
      if (list[i].returnNumber() == tempId) {
        return list[i];
      }
    }
  }
