//Homework 2 part 2

int samples[100];
float pi = 3.141592;
int readVal;

// function prototype
void delay_10Microseconds();

void 
setup() 
{
  Serial.begin(9600);
  int i;
  for (i = 0; i < 100; i++) 
  {
    samples[i]= 31+31*sin((2*pi*i/100)+(.25*sin(16*pi*i/100)));
  }
   
  //Set the ports in PORTB (8-13) to output
  DDRB = B11111111;

}

void 
loop() 
{
  int output, t = 0;
  for (t = 0; t < 100; t++) {

     PORTB = samples[t];

     delay_10Microseconds();
     //Serial.println(sensorValue);
     //readVal = analogRead(A0);
     //Serial.println(readVal);
  }
  //Serial.println(sensorValue);
}


//manual delay function 
//asm code based on
//https://ucexperiment.wordpress.com/2013/06/15/the-lost-art-of-cycle-counting/
void
delay_10Microseconds()
{
    // Example asm notation with the WRONG numbers and WRONG number of noops 
    asm volatile (
     "ldi r20, 40 \n" //Load 10 into r20 
    "1: nop \n" // 1 cycle 
    "dec r20 \n" // decrement the loop counter 1 cycle
    "brne 1b \n" // branch to 1 2 cycles 
    ::: "r20"
  );
  //total cycles is 160
  
}
