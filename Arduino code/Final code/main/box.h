#pragma once
#include "drawer.h"
class box {
  private:

    drawer* list;
    int numberOfDrawers;


  public:
    box();
    box(int, drawer*);
    void addDrawer(/*number*/int, /*pinLed*/ int, /*pinSwitch*/ int, /*interval*/ int = 0, /*numberOfPills*/ int = 0, /*startingHour*/ int = -1);
    //void addDrawer(/*number*/int, /*pinLed*/ int, /*pinSwitch*/ int, /*deadline*/ int[5]);
    void displayBox();
    void activate(int);
    int activated(int);
    void alarmActivated(int*);

    int getStatusDrawer(int);
    int getNumberPills(int);
    void addAlarm(int, int, int, int);

    drawer returnDrawer(int);


};
