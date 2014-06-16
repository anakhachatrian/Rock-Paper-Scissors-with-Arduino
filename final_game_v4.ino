
/* Rock-Paper-Scissors
 * Created by Ana Khachatrian
 * for Arts & Electronics for Designer at UCLAx w/ Pete Hawkes
 
 * This program lets you recreate the game Rock-Paper-Scissors using a slide
 potentiometer to select your move while the machine plays its move at random.
*/



//LEDs for the machine
int pin2 = 2;
int pin3 = 3;
int pin4 = 4;

int blinkCounter = 0;
long timestamp = 0;  // long is a much larger integer
boolean ledState = LOW;   
int delayLength = 500; // how long between intervals 

int randNum;

int gameState = 0; // 0 = 3 LEDs blinking + potentiometer / game play
              //  1 = results

int val = 0; //used to store the state of the input pin

// INPUT: Potentiometer should be connected to 5V and GND
int potPin = 3; // Potentiometer output connected to analog pin 3
int potVal = 0; // Variable to store the input from the potentiometer
int potChoice; // the final choice from each game round

boolean gameResult = false; // did i win or not
boolean tieGame = false;

// LEDs for the potentiometer
int rockPin = 9;   
int paperPin = 10;  
int scissorsPin = 11;  

// Program variables
int rockVal = 0;   // Variables to store the values to send to the pins
int paperVal = 0;
int scissorsVal = 0;

// SOUND
int speakerPin = 8;
#include "musical_notes.h"

void setup() {
  
  randomSeed(analogRead(0));  
    
  pinMode(pin2, OUTPUT); //sets the machines pins as output
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  
  pinMode(rockPin, OUTPUT);   // sets the players pins as output
  pinMode(paperPin, OUTPUT);   
  pinMode(scissorsPin, OUTPUT); 
  
   // Game Sounds
   pinMode(speakerPin, OUTPUT);  
    
  //Serial.begin(9600);
  
  startGame();
  
}

void loop() {
  

  if (gameState == 0) {
    // do the 3 blinks
    blinkThreeTimes(); //this will blink and play sounds
    checkPotentiometer(); // this will check the slider, and turn on corresponding LEDs
    //checkResults(); // keep both LEDs on HIGH
  } else {
     // results 
    playResultSounds(); // play either victory or defeat sound
    restartGame(); // starts the game all over
  }
  
 
}

    


 

 
  
