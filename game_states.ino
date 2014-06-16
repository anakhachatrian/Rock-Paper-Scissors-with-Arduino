void startGame() {
  gameState = 0;
  timestamp = millis(); 
  blinkCounter = 0;
  randomSeed(analogRead(0));
  tieGame = false; 
}

void beep (int speakerPin, float noteFrequency, long noteDuration)
{    
  int x;
  // Convert the frequency to microseconds
  float microsecondsPerWave = 1000000/noteFrequency;
  // Calculate how many HIGH/LOW cycles there are per millisecond
  float millisecondsPerCycle = 1000/(microsecondsPerWave * 2);
  // Multiply noteDuration * number or cycles per millisecond
  float loopTime = noteDuration * millisecondsPerCycle;
  // Play the note for the calculated loopTime.
  for (x=0;x<loopTime;x++)   
          {   
              digitalWrite(speakerPin,HIGH); 
              delayMicroseconds(microsecondsPerWave); 
              digitalWrite(speakerPin,LOW); 
              delayMicroseconds(microsecondsPerWave); 
          } 
}     


void blinkThreeTimes() {

  if ( (millis() - timestamp > delayLength)) {
    ledState = !ledState; // toggles the ledState between true/false
    digitalWrite(pin2, ledState); // make the led change
    digitalWrite(pin3, ledState);
    digitalWrite(pin4, ledState);
    timestamp = millis();
    blinkCounter++;

    //Serial.print("blink:");
    //Serial.println(blinkCounter);

    if (blinkCounter == 6) {
      checkResults(); 
    }
  } 

}

void checkPotentiometer() {
  potVal = analogRead(potPin);   // read the potentiometer value at the input pin
  
  
  //Serial.println(potVal);

  if (potVal < 341)  // Lowest third of the potentiometer's range (0-340)
  {                  
    potVal = (potVal * 3) / 4; // Normalize to 0-255

    rockVal = 256 - potVal;  // Rock from full to off
    paperVal = 1;        // Paper from off to full
    scissorsVal = 1;             // Scissor off
    potChoice = 2;
    rockVal = constrain(rockVal, 0, 255);
    
  }
  else if (potVal < 682) // Middle third of potentiometer's range (341-681)
  {
    potVal = ( (potVal-341) * 3) / 4; // Normalize to 0-255

    rockVal = 1;            // Rock off
    paperVal = 256 - potVal; // Paper from full to off
    scissorsVal = 1;       // Scissor from off to full
    potChoice = 3;
  }
  else  // Upper third of potentiometer"s range (682-1023)
  {
    potVal = ( (potVal-683) * 3) / 4; // Normalize to 0-255

    rockVal = 1;       // Rock from off to full
    paperVal = 1;            // Paper off
    scissorsVal = potVal; // Scissor from full to off
    potChoice = 4;
    scissorsVal = constrain(scissorsVal, 0, 255);
  }
//  
//  Serial.print(rockVal);
//  Serial.print("  :  ");
//  Serial.print(paperVal);
//  Serial.print("  :  ");
//  Serial.println(scissorsVal);
  


  analogWrite(rockPin, rockVal);   // Write values to LED pins
  analogWrite(paperPin, paperVal); 
  analogWrite(scissorsPin, scissorsVal); 
  
 
}


void checkResults() {
  
   gameState = 1; 

  //select random lED
  randNum=random(2,5);
  //turn random LED on
  digitalWrite(randNum, HIGH);
  delay(1000);
  digitalWrite(randNum, LOW);
  
  //Serial.print("potChoice:");
  //Serial.print(potChoice);

  //Serial.print("     random:");
  //Serial.println(randNum);

  if (randNum == potChoice) {
    //Serial.println("TIE GAME"); 
    // TIE GAME
    tieGame = true;
  } 
  else {
    // it's not a tie. you either won or lost
    tieGame = false;
    gameResult = judgeGame(potChoice, randNum);
  }



} 

boolean judgeGame(int potChoice, int randNum) {

  boolean finalResult;

  switch (potChoice) {
  case 2:
    //do something when var equals 2
    if (randNum == 4) {
      finalResult = true; 
    } 
    else {
      finalResult = false;
    }
    //Serial.print("results:");
    //Serial.println(finalResult);
    break;
  case 3:
    //do something when var equals 3
    if (randNum == 2) {
      finalResult = true; 
    } 
    else {
      finalResult = false;
    }
    //Serial.print("results:");
    //Serial.println(finalResult);
    break;
  case 4:
    //do something when var equals 4
    if (randNum == 3) {
      finalResult = true; 
    } 
    else {
      finalResult = false;
    }
    //Serial.print("results:");
    //Serial.println(finalResult);
    /* break;
  default: 
    // if nothing else matches, do the default
    // default is optional
    Serial.print("the switch case broke");
    Serial.println(potChoice);
    finalResult = false; */
  }

  return finalResult;
  
  
}




void playResultSounds() {
  

  if (tieGame == true) {
    //Serial.println("+ + + + + + + + +  TIE SOUND");
    // play tie sounds
    beep(speakerPin, note_A7,100); //A 
    beep(speakerPin, note_G7,100); //G 
    beep(speakerPin, note_E7,100); //E 
    beep(speakerPin, note_C7,100); //C
    beep(speakerPin, note_D7,100); //D 
    beep(speakerPin, note_B7,100); //B 
    /* beep(speakerPin, note_F7,100); //F 
    beep(speakerPin, note_C8,100); //C */
  } 
  else {
    if (gameResult == true) {
      //sound of victory
      
      //Serial.println("+ + + + + + + + +  VICTORY SOUND");
       beep(speakerPin, note_C6,200); //C
          beep(speakerPin, note_E6,200); //E  
          beep(speakerPin, note_G6,200); //G 
          beep(speakerPin, note_C7,200); //C 
          //beep(speakerPin, note_C6,200); //C
          delay(50);
          beep(speakerPin, note_C6,200); //C
          beep(speakerPin, note_E6,200); //E  
          beep(speakerPin, note_G6,200); //G 
          beep(speakerPin, note_C7,200); //C 
          //beep(speakerPin, note_C6,200); //C 
         
    }
    else {
      // play sound of defeat
      //Serial.println("+ + + + + + + + +  DEFEAT SOUND");
     beep(speakerPin, note_Bb3,300); //B b
          delay(200);
          beep(speakerPin, note_C4,300); //C
          delay(200);
          beep(speakerPin, note_Ab3,300); //A b
          delay(500);
          beep(speakerPin, note_Ab2,300); //A b  
  }
  }
  
}

void restartGame() {
  gameState = 0;
  timestamp = millis(); 
  blinkCounter = 0;
  randomSeed(analogRead(0)); 
}



