
/*
 * this is the programing code for knowlegde bowl (andrews eagle project)
 * this is a 3 player button game that has a 15sec timer the the main person has a button to reset the board.
 * we used two libraries in addition to the standard. 
 * LedControl is the code that runs MAX7219 display controller using the SPI BUS 
 * EnableInterrupt allows us to read the buttons as interrupts.
 * this uses a total of 8 digital IO pins and one variable treated as a 16 BIT binary value. 
 * 
 */
#include "LedControl.h"                   //bring in two needed libraries
#include "EnableInterrupt.h"              //for display and button control 

//define our pin assingments
const unsigned int SPI_MOSI = 6;
const unsigned int SPI_CLK = 4;
const unsigned int SPI_CS = 3;  
const unsigned int playerPin1 = 8;
const unsigned int playerPin2 = 9;
const unsigned int playerPin3 = 10;
const unsigned int resetPin = 5;
const unsigned int buzz = 12;

// define our  bit values for our variable "game"
const unsigned int player1_1st = 256;
const unsigned int player1_2nd = 128;
const unsigned int player1_3rd = 64;
const unsigned int player2_1st = 32;
const unsigned int player2_2nd = 16;
const unsigned int player2_3rd = 8;
const unsigned int player3_1st = 4;
const unsigned int player3_2nd = 2;
const unsigned int player3_3rd = 1;
const unsigned int reset_timer = 32768;
const unsigned int start_timer = 16384;
const unsigned int buzz2 = 8192;
//variables for switch debouncing 
long debouncing_time = 100;
volatile unsigned long last_micros;
//how many display chips are we using 
const unsigned int MAX7219_COUNT = 1;
//initialize our game variable 
volatile int  game = 0;
//defining how LedControl will use the pins 
LedControl lc=LedControl(SPI_MOSI,SPI_CLK,SPI_CS,MAX7219_COUNT);
unsigned int x,y,d1,d2;




void setup() {
    /*
     * this function sets up display to be blank initializes the digital pins for inputs 
     * and asigns the interrupts to the buttons
     */
    lc.shutdown(0,false);
    lc.setIntensity(0,8);
    lc.clearDisplay(0);
    pinMode(playerPin1, INPUT_PULLUP);
    pinMode(playerPin2, INPUT_PULLUP);
    pinMode(playerPin3, INPUT_PULLUP);
    pinMode(resetPin, INPUT_PULLUP);
    enableInterrupt(playerPin1, player1_button, CHANGE);
    enableInterrupt(playerPin2, player2_button, CHANGE);
    enableInterrupt(playerPin3, player3_button, CHANGE);
   /* enableInterrupt(resetPin, reset_timer_int_debounce, RISING);*/
    pinMode(buzz, OUTPUT);
}

void player1_button() {
   /*
    * this is a button interrupt for player 1
    * first it checks to see if it has beeen called already 
    * and if it hasn't it checks to see what place it was pressed.
    * it then updates the appropriate bits in the "game" variable.
    */
   if ( not ( game & ( player1_1st + player1_2nd + player1_3rd ) ) ) {
     if ( not ( game & ( player2_1st + player3_1st ) ) ) {
        game = game | ( player1_1st + start_timer );
     }
     else {
       if  ( not (  game & ( player2_2nd + player3_2nd ) ) ) {
          game = game | player1_2nd;
       }
       else {
          game = game | player1_3rd;
       }
     }
   }
   updateDisplay();
}
void player2_button() {
    /*
    * this is a button interrupt for player 2
    * first it checks to see if it has beeen called already 
    * and if it hasn't it checks to see what place it was pressed.
    * it then updates the appropriate bits in the "game" variable.
    */
    if ( not ( game & ( player2_1st + player2_2nd + player2_3rd ) ) ) {
      if ( not ( game & ( player1_1st + player3_1st ) ) ) {
        game = game | ( player2_1st + start_timer );
      }
      else {
        if ( not ( game & ( player1_2nd + player3_2nd ) ) ) {
          game = game | player2_2nd;
        }
        else {
          game = game | player2_3rd;
        }
      }
    }
    updateDisplay();
}


void player3_button() {
    /*
    * this is a button interrupt for player 3
    * first it checks to see if it has beeen called already 
    * and if it hasn't it checks to see what place it was pressed.
    * it then updates the appropriate bits in the "game" variable.
    */
    if ( not ( game & ( player3_1st + player3_2nd + player3_3rd ) ) ) {
      if ( not ( game & ( player1_1st + player2_1st ) ) ) {
        game = game | ( player3_1st + start_timer );
      }
      else  {
        if ( not ( game & ( player1_2nd + player2_2nd ) ) ) {
          game = game | player3_2nd;
        }
        else {
          game = game | player3_3rd;
        }
      }
   }
   updateDisplay();
}


void reset_timer_int_debounce(){
    /*
     * this fuction prevents the reset button mechanical bounce  
     * from over resetting the code 
     */
    if ( ( long ) ( micros() - last_micros ) >= debouncing_time * 1000 ){
      reset_timer_int();
      last_micros - micros();
    }
}


void reset_timer_int() {
      //this is the real reset button interrupt code that clears the reset bit in "game" variable 
      if ( not ( game & reset_timer ) ) {
        game =  game + reset_timer;
      }
   
   
}


void updateDisplay() {
    // this code upates the player placement order on the first three digits 
     
    if ( game & player1_1st ) { lc.setDigit( 0,0,1,0 ); }
    if ( game & player1_2nd ) { lc.setDigit( 0,0,2,0 ); }
    if ( game & player1_3rd ) { lc.setDigit( 0,0,3,0 ); }

    if ( game & player2_1st ) { lc.setDigit( 0,2,1,0 ); }
    if ( game & player2_2nd ) { lc.setDigit( 0,2,2,0 ); }
    if ( game & player2_3rd ) { lc.setDigit( 0,2,3,0 ); }

    if ( game & player3_1st ) { lc.setDigit( 0,4,1,0 ); }
    if ( game & player3_2nd ) { lc.setDigit( 0,4,2,0 ); }
    if ( game & player3_3rd ) { lc.setDigit( 0,4,3,0 ); }

}

void buzzer(){
/* 
 *  makes the buzzer buzz
 */
  digitalWrite( buzz, HIGH );  
  delay(2000);
  digitalWrite( buzz, LOW );
}


void loop() {
  while( not (game & start_timer )) {}
  while (1) {
    
    x = 16;
    while (x > 1){
      x = x-1;
      d1=int( x/10 );
      d2=int( x - ( d1 * 10 ) );
      lc.setDigit( 0,7,d1,0 );
      lc.setDigit( 0,6,d2,0 );
      y=10;
        while (y > 0){
           if  (digitalRead(5)){
             delay(100);
              
           }
           y = y-1;
        }
       
      }
    x = x-1;
    d1=int( x/10 );
    d2=int( x - ( d1 * 10 ) );
    lc.setDigit( 0,7,d1,0 );
    lc.setDigit( 0,6,d2,0 );
    digitalWrite( buzz, HIGH );
    while( digitalRead (5)) {}
    reset_timer_int();
    x = 15;
    d1=int( x/10 );
    d2=int( x - ( d1 * 10 ) );
    lc.setDigit( 0,7
    
    
    
    
    
    
    
    
    
    
    
    
    
    ,d1,0 );
    lc.setDigit( 0,6,d2,0 );
    digitalWrite( buzz, LOW );
    while( not ( digitalRead(5))){}
   }
}   
      
      
     
