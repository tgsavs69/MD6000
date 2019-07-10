#pragma once
#include <Time.h>
#include <TimeAlarms.h>

class drawer {
  private:


    int number; /*id*/
    int pinLed; /* pin used by the led */
    int pinSwitch; /* pin used by the switch */



    int timeBetweenPills; /*the period between taking pills */
    int numberOfPills; /*how many pills to take once*/
    int startingHour; /*when the alarm should be set up */
    int alarmTriggered;
    int drawerOpen = 0;




  public:
    drawer();
    drawer(/*number*/int, /*pinLed*/ int, /*pinSwitch*/ int, /*interval*/ int, /*numberOfPills*/ int, /*startingHour*/ int);
    drawer(/*number*/int, /*pinLed*/ int, /*pinSwitch*/ int);
    drawer(const drawer&);
    drawer& operator=(const drawer&);

    void clone(/*number*/int, /*pinLed*/ int, /*pinSwitch*/ int, /*interval*/ int = 0, /*numberOfPills*/ int = 0, /*startingHour*/ int = 0);

    void toggleLED(int);
  //  void activated();
    int  activated();
    void activate();
    void displayDrawer();
    void setupAlarm();

    void addAlarm(int, int, int);
    void removeAlarm(int, int, int);
    int  statusDrawer();
    void takePills();

    int returnNumber();
    int returnPills();


    int compareDeadline(int[5]);

};
