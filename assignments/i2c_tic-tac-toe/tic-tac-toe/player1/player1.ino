#include "Wire.h"
#define RED 12
#define BLUE 8

char board[9] = {'e','e','e','e','e','e','e','e','e'};
short winner = 0;
int count =0;


void setup() {
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
  Wire.setTimeout(10000);
  Serial.setTimeout(10000);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  switch(winner){

    case 0:{
      playGame();
      break;
    }

    case 1:{
      p1led();
      Serial.println("p1 win");
      break;
    }

    case 2:{
      p2led();
      Serial.println("p2 win");
      break;
    }
    case 3:{
      Serial.println("Tie! you both suck...");
      p1led();
      p2led();
      break;
    }

 }
}

void playGame(){
  if(count == 9){
    winner =3;
  }
  printBoard();
  Serial.print("Where would you like to move?\n");
  while(Serial.available()==0){}
  short loc = (Serial.read()-48);
  boolean check = (board[loc] == 'e' && loc>(-1) && loc<9);

  while(!check){
    Serial.print("That space is already taken!\n");
    Serial.print("Where would you like to move?\n");
    while(Serial.available()==0){}
    loc = (Serial.read()-48);
    check = (board[loc] == 'e' && loc>(-1) && loc<9);
  }

  board[loc] = 'X';
  count++; //increments a counter of total moves to catch the tie case
  printBoard();
  if(win()){
    winner = 1;
    return;
  }
  if(count ==9){
    winner =3;
    return;
  }

  Wire.beginTransmission(8);
  Serial.println("writing....");
  Wire.write(loc);
  Wire.endTransmission();

  delay(1000);

  Wire.beginTransmission(8);
  Wire.write(9);
  Wire.endTransmission();
  delay(10000); //tells slave to prompt player for a move; intentionally long delay.

  Wire.requestFrom(8, 1);
  while(Wire.available()==0){
    //blocking until there is something to be read
  }
  short index = (Wire.read());

  board[index] = 'O';
  count++; //increments a counter of total moves to catch the tie case

  if(win()){
    winner = 2;
    return;
  }
}

boolean win(){
  //while this reads very obscure, it prevents looping and over the top memory access times. No external functions or branching to take up extra time here!

  return ( (board[0]==board[1] && board[1]==board[2] && board[1]!='e')||(board[3]==board[4] && board[4]==board[5] && board[5]!='e')
            ||(board[6]==board[7] && board[7]==board[8] && board[8]!='e')||(board[0]==board[3] && board[3]==board[6] && board[6]!='e')
              ||(board[1]==board[4] && board[4]==board[7] && board[7]!='e')||(board[2]==board[5] && board[5]==board[8] && board[8]!='e')
                ||(board[0]==board[4] && board[4]==board[8] && board[8]!='e')||(board[2]==board[4] && board[4]==board[6] && board[6]!='e'));
}

void p1led(){
  digitalWrite(RED, HIGH);
  }

void p2led(){
  digitalWrite(BLUE, HIGH);
  }

void printBoard(){
  Serial.println("---------------");
  Serial.print(" | ");
  Serial.print(board[0]);
  Serial.print(" | ");
  Serial.print(board[1]);
  Serial.print(" | ");
  Serial.print(board[2]);
  Serial.println(" | ");
  Serial.println("---------------");
  Serial.print(" | ");
  Serial.print(board[3]);
  Serial.print(" | ");
  Serial.print(board[4]);
  Serial.print(" | ");
  Serial.print(board[5]);
  Serial.println(" | ");
  Serial.println("---------------");
  Serial.print(" | ");
  Serial.print(board[6]);
  Serial.print(" | ");
  Serial.print(board[7]);
  Serial.print(" | ");
  Serial.print(board[8]);
  Serial.println(" | ");
  Serial.println("---------------");
}
