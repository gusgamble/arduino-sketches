//Team: segmentation fault
//Members: Gus Gamble, Sam Frey
#include "Arduino.h"


int anPin = 0 ;
int readVal = 0 ;

int redPin = 9;
int greenPin = 11 ;
int bluePin = 10 ;

void setup(){
  Serial.begin(9600) ;
  pinMode( redPin, OUTPUT ) ;
  pinMode( greenPin, OUTPUT ) ;
  pinMode( bluePin, OUTPUT ) ;
}
 
void loop(){
  readVal = analogRead(anPin) ;
  Serial.println(readVal) ;


  if( readVal <= 341 ){
    analogWrite( redPin, 255);
    analogWrite( greenPin, 0);
    analogWrite( bluePin, 0);
  }
  else if( readVal >= 342 && readVal <682){
    analogWrite( redPin, 0);
    analogWrite( greenPin, 255);
    analogWrite( bluePin, 0);
  }
  else if( readVal > 683 ){
      analogWrite( redPin, 0);
      analogWrite( greenPin, 0);
      analogWrite( bluePin, 255);
  }
  else{
    Serial.println("IMPOSSIBLE CONDITION!!!!") ;
  }
}
