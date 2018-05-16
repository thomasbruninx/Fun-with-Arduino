#include <SimpleList.h>

#define NOTE_D1  98
#define NOTE_E1  196
#define NOTE_F1  392
#define NOTE_G1  784


// LED pins
const int led1 = 5;
const int led2 = 4;
const int led3 = 3;
const int led4 = 2;

// Button pins
const int btn1 = 12;
const int btn2 = 11;
const int btn3 = 10;
const int btn4 = 9;

// Button state
int btn1State = 0;
int btn2State = 0;
int btn3State = 0;
int btn4State = 0;

// Variable to store pattern of current game
SimpleList <int> currentSong;
// Variable to store the current level
int currentLevel = 0;


void setup() {
  // Set LED pins as output
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  
  // Set button pins as input
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);
  
  // Get new random seed through analog noise
  randomSeed(analogRead(0));
}
  
void loop() {
  // Variable to store correct presses every turn 
  int goodNotes = 0;
  // Variable to store if last press was correct
  boolean ok = false;
  
  // Level up at the begin of every turn
  levelUp();

  do {
    int input = readButtons();
    ok = checkNote(goodNotes, input);
    goodNotes++;
  } while(goodNotes < currentLevel && ok);
  
  if (!ok) {
    currentSong.clear();
    currentLevel = 0;
  }
  
  delay(1500);
}

void levelUp() {
  currentLevel++;
  int randNote = random(1,5);
  
  currentSong.push_back(randNote);

  playSong();
}

boolean checkNote(int pos, int value) {
  int i = 0;
  for (SimpleList<int>::iterator itr = currentSong.begin(); itr != currentSong.end(); ++itr) {
     if (i == pos) {
       if ((*itr) == value) {
         return true;
       }else{
         return false; 
       }
     }
     i++;
  }
}

void playSong() {
  for (SimpleList<int>::iterator itr = currentSong.begin(); itr != currentSong.end(); ++itr) { 
    switch (*itr){
    case 1:
      digitalWrite(led1, HIGH);
      tone(7, NOTE_D1, 1000/8);
      delay(1000);
      digitalWrite(led1, LOW);
      noTone(7);
      break;
    case 2:
      digitalWrite(led2, HIGH);
      tone(7, NOTE_E1, 1000/8);
      delay(1000);
      digitalWrite(led2, LOW);
      noTone(7);
      break;
    case 3:
      digitalWrite(led3, HIGH);
      tone(7, NOTE_F1, 1000/8);
      delay(1000);
      digitalWrite(led3, LOW);
      noTone(7);
      break;
    case 4:
      digitalWrite(led4, HIGH);
      tone(7, NOTE_G1, 1000/8);
      delay(1000);
      digitalWrite(led4, LOW);
      noTone(7);
      break;
    }
    delay(400);
  }
}

int readButtons(){
  int down;
  
  do {
    btn1State = digitalRead(btn1); 
    btn2State = digitalRead(btn2); 
    btn3State = digitalRead(btn3); 
    btn4State = digitalRead(btn4); 
  
    if (btn1State == LOW) {
      down = 1;
      digitalWrite(led1, HIGH);
      tone(7, NOTE_D1, 1000/8);
      delay(500);
      digitalWrite(led1, LOW);
      noTone(7);
    } else if (btn2State == LOW) {
      down = 2;
      digitalWrite(led2, HIGH);
      tone(7, NOTE_E1, 1000/8);
      delay(500);
      digitalWrite(led2, LOW);
      noTone(7);
    } else if (btn3State == LOW) {
      down = 3;
      digitalWrite(led3, HIGH);
      tone(7, NOTE_F1, 1000/8);
      delay(500);
      digitalWrite(led3, LOW);
      noTone(7);
    } else if (btn4State == LOW) {
      down = 4;
      digitalWrite(led4, HIGH);
      tone(7, NOTE_G1, 1000/8);
      delay(500);
      digitalWrite(led4, LOW);
      noTone(7);
    } else {
      down = 0;
    }  
  }while(down == 0);

  return down;
}
