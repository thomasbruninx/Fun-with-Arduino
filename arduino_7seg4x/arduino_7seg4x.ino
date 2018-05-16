
byte latchPin = 5;
byte clockPin = 4;
byte dataPin = 6;
byte btn1Pin = 8;
byte btn2Pin = 7;
byte dispPins[4] = {12, 11, 10, 9};
byte dispData[4] = {B11111111, B11111111, B11111111, B11111111};


byte numbers[16] = {B01111110, B00001100, B10110110, B10011110, B11001100, B11011010, B11111010, B00001110, B11111110, B11011110, B11101110, B11111000, B01110010, B10111100, B11100010};

int maxStep = 5;
int curStep = 0;
byte steps[5][4] = {{numbers[1], numbers[9], numbers[4], numbers[6]},
                    {numbers[1], numbers[9], numbers[6], numbers[6]},
                    {numbers[1], numbers[9], numbers[9], numbers[8]}, 
                    {numbers[2], numbers[0], numbers[1], numbers[7]},
                    {numbers[2], numbers[0], numbers[1], numbers[8]}};

void loadShift(byte input);
void loadData(byte input[4]);

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(btn1Pin, INPUT);
  pinMode(btn2Pin, INPUT);
  for (int i = 0; i < 4; ++i) {
    pinMode(dispPins[i], OUTPUT);
    digitalWrite(dispPins[i], HIGH);
  }
  digitalWrite(dispPins[0], LOW);
  digitalWrite(dispPins[1], LOW);
  digitalWrite(dispPins[2], LOW);
  digitalWrite(dispPins[3], LOW);
}

void loop() {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      digitalWrite(dispPins[j], HIGH);
    }
    loadShift(dispData[i]);
    digitalWrite(dispPins[i], LOW);
    delayMicroseconds(200);
  }
  if (digitalRead(btn1Pin) == HIGH) {
    if (++curStep >= maxStep) {
      curStep = 0;
    }
    loadData(steps[curStep]);
    delay(100);
  }
  if (digitalRead(btn2Pin) == HIGH) {
    if (--curStep < 0) {
      curStep = maxStep-1;
    }
    loadData(steps[curStep]);
    delay(100);
  }
}

void loadData(byte input[4]) {
  for (int i = 0; i < 4; ++i) {
    dispData[i] = input[3-i];
  }
}

void loadShift(byte input) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, input);  
  digitalWrite(latchPin, HIGH);
}
