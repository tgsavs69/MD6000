#include <TimeAlarms.h>

#include <Time.h>
#include <TimeLib.h>

#define _DISABLE_TLS_
#define _DEBUG_

#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

#define USERNAME "tgsavs"
#define DEVICE_ID "living123"
#define DEVICE_CREDENTIAL "esp8266"
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
int systolicReading = 0;
int diastolicReading = 0;
int state = 0;
void setup() {

  Serial.begin(9600);
  thing.add_wifi("DIGI-4d95", "2pJhKaH3");

  thing["bloodPressure"] >> [](pson & out) {
    out["systolic"] = systolicReading;
    out["diastolic"] = diastolicReading;
  };


}

long t = millis();
void loop() {
  // handle connection
  thing.handle();
 

  if (state == HIGH) {
    long t = millis();
    while (millis() - t < 5000) {
      thing.handle();
      yield();
    }
    Serial.print("measure pressure#");
    delay(2000);
    state = LOW;
    

  }

thing["upload"] << inputValue(state);
  if (Serial.available()) {
    delay(100);
    String message = "";
    char c = Serial.read();
    long timeout = millis();

    while (c != '#' && millis() - timeout < 5000) {
      message += c;
      c = Serial.read();
      delay(10);
    }



    if ( message.length() > 19 && message.substring(0, 14) == "blood pressure" ) {
      String firstValue = message.substring(15, 18);
      String secondValue = message.substring(19, 22);
      systolicReading = firstValue.toInt();
      diastolicReading = secondValue.toInt();
      thing.write_bucket("bloodPressure", "bloodPressure");
      Serial.print("PRESSURE GOT ->");
      Serial.print(firstValue);
      Serial.print(" si ");
      Serial.print(secondValue);
      Serial.println("#");
    }



  }
  /*
    if (millis() - t > 10000) {
      // write to bucket BucketId the TempHum resource
      thing.write_bucket("bloodPressure", "bloodPressure");
      t = millis();
    }

  */
}
