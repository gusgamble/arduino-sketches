
#include <Wire.h>
char board[9] = {'e','e','e','e','e','e','e','e','e'};
boolean makeMove = false;
short sLoc;
void setup() {
  // put your setup code here, to run once:
  Wire.begin(8);                // join i2c bus with address #8
  Serial.begin(9600);
  Wire.onRequest(requestEvent); 
  Wire.onReceive(receiveEvent);
  Wire.setTimeout(100000);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  //if the slave needs to make a move, we will get the input and check it
  if(makeMove){
    sLoc = NULL;
    printBoard();
    Serial.println("Where would you like to move: ");
  
    while(Serial.available()==0){
      //block for the serial read
      }
    //get our value and convert to short
    sLoc = (Serial.read()-48);
    delay(500);
    //see if valid
    boolean check = (board[sLoc]== 'e' && sLoc>(-1) && sLoc<9);

    //if invalid, ask until we get a valid move
    while(!check){
      Serial.print("That space is already taken!\n");
      Serial.print("Where would you like to move: ");
      //block for the read
      delay(500);
      while(Serial.available()==0){}
      sLoc = (Serial.read()-48);
      check = board[sLoc]== 'e' && sLoc>(-1) && sLoc<9;
    }
    //place our move, print the board, and stop asking for a new move
    board[sLoc] = 'O';
    printBoard();
    makeMove = false;
  }

}

void requestEvent() {
  //send the valid move
  Wire.write(sLoc);
  // respond with message of sizeOf(int) or 1 byte
  // as expected by master
}

void receiveEvent(int howMany){
  //read the move, trusting that anything sent over the wire is correct
  short loc = Wire.read();
  if(loc ==9){
    makeMove = true;
    return;
  }
  //store the move on the board
  board[loc] = 'X';
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
