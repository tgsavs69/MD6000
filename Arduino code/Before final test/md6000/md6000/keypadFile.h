#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
// sorin
  byte rowPins[ROWS] = {13, 12, 11, 10}; //connect to the row pinouts of the keypad
  byte colPins[COLS] = {9, 8,7}; //connect to the column pinouts of the keypad



/* tareq
byte rowPins[ROWS] = {12, 17, 8, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {11, 13, 9}; //connect to the column pinouts of the keypad
*/
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
