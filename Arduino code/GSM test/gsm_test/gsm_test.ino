#include <SoftwareSerial.h>



void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  Serial3.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  Serial3.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  Serial3.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  Serial3.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  Serial3.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
}

void loop()
{
  updateSerial();
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    Serial3.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(Serial3.available()) 
  {
    Serial.write(Serial3.read());//Forward what Software Serial received to Serial Port
  }
}
