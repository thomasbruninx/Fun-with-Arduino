#include <Keypad.h>
#define DEBUG

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'0', '1', '2', '3'},
  {'4', '5', '6', '7'},
  {'8', '9', 'A', 'B'},
  {'C', 'D', 'E', 'F'}
};
byte rowPins[ROWS] = {8, 7, 6, 5};
byte colPins[COLS] = {9, 10, 11, 12};

byte latchPin = 4;
byte clockPin = 3;
byte dataPin = 2;

Keypad kp = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void loadShift(byte input);

void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  loadShift(B01111111);
}

void loop() {
 char key = kp.getKey();

  if (key != NO_KEY){
    #ifdef DEBUG
    Serial.println(key);
    #endif
    switch (key) {
      case '0':
        loadShift(B11000000);
        break;
      case '1':
        loadShift(B11111001);
        break;
      case '2':
        loadShift(B10100100);
        break;
      case '3':
        loadShift(B10110000);
        break;
      case '4':
        loadShift(B10011001);
        break;
      case '5':
        loadShift(B10010010);
        break;
      case '6':
       	loadShift(B10000010);
        break;
      case '7':
        loadShift(B11111000);
        break;
      case '8':
        loadShift(B10000000);
        break;
      case '9':
        loadShift(B10010000);
        break;
      case 'A':
        loadShift(B10001000);
        break;
      case 'B':
        loadShift(B10000011);
        break;
      case 'C':
        loadShift(B11000110);
        break;
      case 'D':
        loadShift(B10100001);
        break;
      case 'E':
        loadShift(B10000110);
        break;
      case 'F':
        loadShift(B10001110);
        break;
      default:
        loadShift(B01111111);
    }
  }

}

void loadShift(byte input) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, input);  
  digitalWrite(latchPin, HIGH);
  delay(100);
}
