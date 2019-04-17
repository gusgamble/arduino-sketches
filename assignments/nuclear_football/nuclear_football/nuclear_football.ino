#include <Keypad.h>

#include <Keypad.h>

/**
 * CSCI 3410 S17 Lab 02
 * "Nuclear Football"
 * Fill the gaps in this sketch to complete the circuit
 * Refer to the specification in "lab02.pdf" for more details
 * Author: Phil Lopreiato, Spring 2017
 */

/* TODO: Change these to correspond to your actual circuit */
#define BUTTON_IN 10
#define RED_OUT 11
#define BLUE_OUT 12

//layout of the pins for 7-segment
#define gPin A0
#define fPin A1
#define aPin A2
#define bPin 9
#define ePin A3
#define dPin A4
#define cPin A5

/* TODO: Change this if you'd like a different timer value */
#define FUSE_SEC 10
#define MILLIS_PER_SECOND 1000

/* TODO: Put the correct PIN code in this array */
#define PIN_LENGTH 4
const char correct_pin[PIN_LENGTH] = {'1', '2', '3', '4'};

/* Possible Program States */
typedef enum STATES {
  UNARMED,
  ARMED,
  DEFUSED,
  INCORRECT,
  DONE
} STATE;

/* TODO: Initialzie the keypad library here */
char keys[4][3] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[4] = {8,7,6,5};
byte colPins[3] = {4,3,2};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, 4, 3 );

/* This variable stores the current state of the program */
STATE state;

/* Forward declare a function for each state
 * TODO: You will be implementing these functions
 */
void state_unarmed(void);
void state_armed(void);
void state_defused(void);
void state_boom(void);

void setup() {
  //configure serial monitor
  Serial.begin(9600);

  state = UNARMED;

  // Init I/O pins
  pinMode(BUTTON_IN, INPUT);
  pinMode(RED_OUT, OUTPUT);
  pinMode(BLUE_OUT, OUTPUT);

  //7 pin init
  pinMode(gPin, OUTPUT);
  pinMode(fPin, OUTPUT);
  pinMode(aPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(ePin, OUTPUT);
  pinMode(dPin, OUTPUT);
  pinMode(cPin, OUTPUT);
  displayNum(10);
}


void displayNum(int numToDisplay){
  if (numToDisplay == 0){
    digitalWrite(gPin, HIGH);
    digitalWrite(fPin, LOW);
    digitalWrite(ePin, LOW);
    digitalWrite(dPin, LOW);
    digitalWrite(cPin, LOW);
    digitalWrite(bPin, LOW);
    digitalWrite(aPin, LOW);
  }
  else if (numToDisplay == 1){
    digitalWrite(gPin, HIGH);
    digitalWrite(fPin, HIGH);
    digitalWrite(ePin, HIGH);
    digitalWrite(dPin, HIGH);
    digitalWrite(cPin, LOW);
    digitalWrite(bPin, LOW);
    digitalWrite(aPin, HIGH);
  }
  else if(numToDisplay == 2){
    digitalWrite(gPin, LOW);
    digitalWrite(fPin, HIGH);
    digitalWrite(ePin, LOW);
    digitalWrite(dPin, LOW);
    digitalWrite(cPin, HIGH);
    digitalWrite(bPin, LOW);
    digitalWrite(aPin, LOW);
  }
  else if (numToDisplay == 3){
    digitalWrite(gPin, LOW);
    digitalWrite(fPin, HIGH);
    digitalWrite(ePin, HIGH);
    digitalWrite(dPin, LOW);
    digitalWrite(cPin, LOW);
    digitalWrite(bPin, LOW);
    digitalWrite(aPin, LOW);
  }
  else if (numToDisplay == 4){
    digitalWrite(gPin, LOW);
    digitalWrite(fPin, LOW);
    digitalWrite(ePin, HIGH);
    digitalWrite(dPin, HIGH);
    digitalWrite(cPin, LOW);
    digitalWrite(bPin, LOW);
    digitalWrite(aPin, HIGH);
  }
  else if (numToDisplay == 5){
    digitalWrite(gPin, LOW);
    digitalWrite(fPin, LOW);
    digitalWrite(ePin, HIGH);
    digitalWrite(dPin, LOW);
    digitalWrite(cPin, LOW);
    digitalWrite(bPin, HIGH);
    digitalWrite(aPin, LOW);
  }
  else if (numToDisplay == 6){
    digitalWrite(gPin, LOW);
    digitalWrite(fPin, LOW);
    digitalWrite(ePin, LOW);
    digitalWrite(dPin, LOW);
    digitalWrite(cPin, LOW);
    digitalWrite(bPin, HIGH);
    digitalWrite(aPin, LOW);
  }
  else if (numToDisplay == 7){
    digitalWrite(gPin, HIGH);
    digitalWrite(fPin, HIGH);
    digitalWrite(ePin, HIGH);
    digitalWrite(dPin, HIGH);
    digitalWrite(cPin, LOW);
    digitalWrite(bPin, LOW);
    digitalWrite(aPin, LOW);
  }
  else if (numToDisplay == 8){
    digitalWrite(gPin, LOW);
    digitalWrite(fPin, LOW);
    digitalWrite(ePin, LOW);
    digitalWrite(dPin, LOW);
    digitalWrite(cPin, LOW);
    digitalWrite(bPin, LOW);
    digitalWrite(aPin, LOW);
  }
  else if (numToDisplay == 9){
    digitalWrite(gPin, LOW);
    digitalWrite(fPin, LOW);
    digitalWrite(ePin, HIGH);
    digitalWrite(dPin, LOW);
    digitalWrite(cPin, LOW);
    digitalWrite(bPin, LOW);
    digitalWrite(aPin, LOW);
  }
  else{
    digitalWrite(gPin, HIGH);
    digitalWrite(fPin, HIGH);
    digitalWrite(ePin, HIGH);
    digitalWrite(dPin, HIGH);
    digitalWrite(cPin, HIGH);
    digitalWrite(bPin, HIGH);
    digitalWrite(aPin, HIGH);
  }
}

void loop() {
  /* Main program loop
   * Based on the current state, run a different function
   */
  
  switch (state) {
  case UNARMED:
    // Wait for a button press to trigger the countdown
    delay(10);
    state_unarmed();
    break;
  case ARMED:
    // Read in a code from the keyboard and validate it
    Serial.println("ARMED!");
    state_armed();
    delay(250);
    break;
  case DEFUSED:
    // Wooho!
    state_defused();
    break;
  case INCORRECT:
    // Awww
    state_boom();
    break;
  case DONE:
    // Nothing to do, press Arduino reset button to try again
    delay(1000);
    Serial.println("DONE");
    break;
  }
}

void state_defused() {
  //TODO implement this state
  digitalWrite(BLUE_OUT, HIGH);
  digitalWrite(RED_OUT, LOW);
  Serial.println("DEFUSED!");
  state = DONE;
}

void state_boom() {
  //TODO implement this state
  digitalWrite(RED_OUT, HIGH);
  Serial.println("BOOM!");
  state = DONE;
}

void state_armed() {
  //TODO implement this state
  /* NOTE: If you need to store a variable between invocations of
   * this function, you may declare them as static.
   */
   char key;
   int index=0;
   int ledstate = LOW;
   int countdown = 9;
   int wrong = 0;
   digitalWrite(RED_OUT, ledstate);
   long tracktime = millis();
   long blinktime = tracktime;
   long printtime = tracktime;
   while(countdown>=0){
    if(index == 4){
     switch (wrong){
      case 0:
      state = DEFUSED;
      return;

      case 1:
      state = INCORRECT;
      return;
     }
     
    }
    tracktime = millis();
    if(tracktime-blinktime>=125 && ledstate == LOW){
      digitalWrite(RED_OUT, HIGH);
      ledstate = HIGH;
      blinktime = tracktime;
     }
    if(tracktime-blinktime>=125 && ledstate == HIGH){
      digitalWrite(RED_OUT, LOW);
      ledstate = LOW;
      blinktime = tracktime;
    }
    if(tracktime-printtime>=1000){
      Serial.println(countdown);
      displayNum(countdown);
      countdown--;
      printtime = tracktime;
    }
    key = keypad.getKey();
    if(key && key != correct_pin[index]){
      wrong = 1;
      index++;
    }
    else if(key && key == correct_pin[index])
      index++;  
  }
  state = INCORRECT;
 }      

void state_unarmed() {
  //TODO implement this state
  /* NOTE: You must debounce the button input. Select one of the
   * methods of debouncing we discussed in class and implement it
   */
   int currentState = digitalRead(BUTTON_IN);
   int counter = 0;
   long time = 0;
   while(state == UNARMED){
    if(millis()!=time){
      int reading = digitalRead(BUTTON_IN);
      if(reading == currentState && counter >0)
        counter--;
      if (reading != currentState)
        counter++;
      if(counter>=10){
        state = ARMED;
        return;
       }
      time = millis();
   }
  }
}
