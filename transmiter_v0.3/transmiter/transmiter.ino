#include <SoftwareSerial.h>
#include <TimeAlarms.h>
#include <Time.h>
#include <TimeLib.h>



#define _DEBUG_
#define _DISABLE_TLS_
#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

#include <EEPROM.h>
#include <Arduino.h>  // for type definitions



#define USERNAME "tgsavs"
#define DEVICE_ID "living123"
#define DEVICE_CREDENTIAL "esp8266"


ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);



SoftwareSerial mySerial(D1, D2); // RX, TX

template <class T> int EEPROM_writeAnything(int ee, const T& value)
{
  const byte* p = (const byte*)(const void*)&value;
  unsigned int i;
  for (i = 0; i < sizeof(value); i++)
    EEPROM.write(ee++, *p++);
  return i;
}

template <class T> int EEPROM_readAnything(int ee, T& value)
{
  byte* p = (byte*)(void*)&value;
  unsigned int i;
  for (i = 0; i < sizeof(value); i++)
    *p++ = EEPROM.read(ee++);
  return i;
}



struct drawer {
  int startingHour;
  int numberOfPills;
  int interval;

  int overtime;

} ;

drawer drawers[6];


/*
void transmit() {
  for (int i = 0; i < 6; i++) {


    Serial.print("Drawer ");
    Serial.println(String(i + 1));
    Serial.print("Starting hour -> ");
    Serial.print(drawers[i].startingHour);
    Serial.print(" | Number of pills to take -> ");

    Serial.print(drawers[i].numberOfPills);
    Serial.print(" | Period ->");
    Serial.print(drawers[i].interval);
    Serial.println(" h");
  }
}
*/
int hourA, pillsA, periodA;


int state = 0;
int val;
int uploaded = 0;
void setup()
{
  EEPROM.begin(512);
  EEPROM_readAnything(0, drawers);

  mySerial.begin(9600);
  Serial.begin(9600);

  Serial.println("a inceput");

  pinMode(BUILTIN_LED, OUTPUT);

  thing.add_wifi("DIGI-4d95", "2pJhKaH3");

  transmit();

  thing["hourDrawer1"] << inputValue(drawers[0].startingHour);
  thing["pillsDrawer1"] << inputValue(drawers[0].numberOfPills);
  thing["periodDrawer1"] << inputValue(drawers[0].interval);

  thing["hourDrawer2"] << inputValue(drawers[1].startingHour);
  thing["pillsDrawer2"] << inputValue(drawers[1].numberOfPills);
  thing["periodDrawer2"] << inputValue(drawers[1].interval);


  thing["hourDrawer3"] << inputValue(drawers[2].startingHour);
  thing["pillsDrawer3"] << inputValue(drawers[2].numberOfPills);
  thing["periodDrawer3"] << inputValue(drawers[2].interval);

  thing["hourDrawer4"] << inputValue(drawers[3].startingHour);
  thing["pillsDrawer4"] << inputValue(drawers[3].numberOfPills);
  thing["periodDrawer4"] << inputValue(drawers[3].interval);

  thing["hourDrawer5"] << inputValue(drawers[4].startingHour);
  thing["pillsDrawer5"] << inputValue(drawers[4].numberOfPills);
  thing["periodDrawer5"] << inputValue(drawers[4].interval);

  thing["hourDrawer6"] << inputValue(drawers[5].startingHour);
  thing["pillsDrawer6"] << inputValue(drawers[5].numberOfPills);
  thing["periodDrawer6"] << inputValue(drawers[5].interval);

  val = 15;
  uploaded = 0;
  thing["took"] << inputValue(val);
  thing["uploaded"] << inputValue(uploaded);
}




  void transmit() {
  static int count = 0;
  mySerial.write('a');
  long t = millis();
  while (millis() - t < 5000) {

    if (mySerial.available()) {
      char c = mySerial.read();
      if ( c == 'k') {
        for (int i = 0; i < 6; i++) {


          Serial.print("Drawer ");
          Serial.println(String(i + 1));
          Serial.print("Starting hour -> ");
          Serial.print(drawers[i].startingHour);
          Serial.print(" | Number of pills to take -> ");

          Serial.print(drawers[i].numberOfPills);
          Serial.print(" | Period ->");
          Serial.print(drawers[i].interval);
          Serial.println(" h");

          mySerial.print(drawers[i].startingHour);
          mySerial.print('x');

          mySerial.print(drawers[i].numberOfPills);
          mySerial.print('x');

          mySerial.print(drawers[i].interval);
          mySerial.print('x');
          yield();
        }
        uploaded = 2;
      }
    }
    yield();
  }
  }


long temp = millis();
bool refresh = LOW;

void loop()
{
  if (state == HIGH) {
    long t = millis();
    while (millis() - t < 3000) {
      thing.handle();
      yield();
    }




    state = LOW;
    transmit();
    EEPROM_writeAnything(0, drawers);
    EEPROM.commit();
  }else{
    uploaded = 0;
  }
  thing.handle();
  thing["upload"] << inputValue(state);
  thing["refresh"] << inputValue(refresh);








}
