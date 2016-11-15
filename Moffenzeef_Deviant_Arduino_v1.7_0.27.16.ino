/*
        Moffenzeef Modular
              Deviant
  Created by Ross Fish July 2015
           CC-BY-NC-SA
    http://moffenzeefmodular.com

  /////////////////////////////////////////////////////////////////
            PINOUT
/////////////////////////////////////////////////////////////////

  /////DIGITAL INS//////
  Pin 2 - Bang! 1 Input
  Pin 3 - Bang! 2 Input

  /////DIGITAL OUTS//////
  Pin 13 - LED Power indicator

  /////ANALOG INS - POTS//////
  A0 - Low 1
  A1 - Hi 1
  A4 - Low 2
  A5 - Hi 2

  /////ANALOG INS - JACKS//////
  A2 - Low CV Input 1
  A3 - High CV Input 1
  A6 - Low CV Input 2
  A7 - High CV Input 2

  /////ANALOG OUTS//////
  Pin 5 - Out 1
  Pin 6 - Out 2

*/

int trigStateOne = 0; // variable to hold current trigger state
int lastTrigStateOne = 0; // variable to hold previous trigger state

int trigStateTwo = 0; // variable to hold current trigger state
int lastTrigStateTwo = 0; // variable to hold previous trigger state

int lowOne = 0;
int lowOneCvRaw = 0;
int lowOneCvScaled = 0; 
int lowOneMath = 0;
int pot0Raw = 0;

int highOne = 0;
int highOneCvRaw = 0;
int highOneCvScaled = 0; 
int highOneMath = 0;
int pot1Raw = 0;

int lowTwo = 0;
int lowTwoCvRaw = 0;
int lowTwoCvScaled = 0; 
int lowTwoMath = 0;
int pot4Raw = 0;

int highTwo = 0;
int highTwoCvRaw = 0;
int highTwoCvScaled = 0; 
int highTwoMath = 0;
int pot5Raw = 0;

int outOne = 0;
int outTwo = 0;

void setup() {
  randomSeed(analogRead(0));   // reseed random number generator
  pinMode(2, INPUT); 
  pinMode(4, INPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
}

void loop() {

  pot0Raw = analogRead(A0);
  lowOneCvRaw = analogRead(A3);
  
  lowOneCvScaled = map(lowOneCvRaw, 1, 1023, -512, 512);

  lowOneMath = pot0Raw + lowOneCvScaled;

  lowOneMath = max(lowOneMath, 1);   // limit the lowest possible value to 1, data below this limit gets truncated
  lowOneMath = min(lowOneMath, 1023); // limit the highest possible value to 1023, data above this limit gets truncated
  
  lowOne = map(lowOneMath, 1, 1023, 0, 255);

  /////////////////////////////////////////////////////////////////////

  pot1Raw = analogRead(A1);
  highOneCvRaw = analogRead(A2); 

  highOneCvScaled = map(highOneCvRaw, 1, 1023, -512, 512); 

  highOneMath = pot1Raw + highOneCvScaled;
  
  highOneMath = max(highOneMath, 1);   // limit the lowest possible value to 1, data below this limit gets truncated
  highOneMath = min(highOneMath, 1023); // limit the highest possible value to 1023, data above this limit gets truncated
  
  highOne = map(highOneMath, 1, 1023, 0, 255);

  /////////////////////////////////////////////////////////////////////

  pot5Raw = analogRead(A5);
  lowTwoCvRaw = analogRead(A7);

  lowTwoCvScaled = map(lowTwoCvRaw, 1, 1023, -512, 512);

  lowTwoMath = pot5Raw + lowTwoCvScaled; 

  lowTwoMath = max(lowTwoMath, 1);   // limit the lowest possible value to 1, data below this limit gets truncated
  lowTwoMath = min(lowTwoMath, 1023); // limit the highest possible value to 1023, data above this limit gets truncated
  
  lowTwo = map(lowTwoMath, 1, 1023, 0, 255);
  /////////////////////////////////////////////////////////////////////

  pot4Raw = analogRead(A4);
  highTwoCvRaw = analogRead(A6);

  highTwoCvScaled = map(highTwoCvRaw, 1, 1023, -512, 512); 

  highTwoMath = pot4Raw + highTwoCvScaled; 
  
  highTwoMath = max(highTwoMath, 1);   // limit the lowest possible value to 1, data below this limit gets truncated
  highTwoMath = min(highTwoMath, 1023); // limit the highest possible value to 1023, data above this limit gets truncated
  
  highTwo = map(highTwoMath, 1, 1023, 0, 255);
  
  /////////////////////////////////////////////////////////////////////

  if (lowOne > highOne) {   // Prevents low value from being higher than high value
    lowOne = highOne;
  }
  else {
    lowOne = lowOne;
  }

  /////////////////////////////////////////////////////////////////////


  if (lowTwo > highTwo) {   // Prevents low value from being higher than high value
    lowTwo = highTwo;
  }
  else {
    lowTwo = lowTwo;
  }

  /////////////////////////////////////////////////////////////////////

  trigStateOne = digitalRead(2); // read trigger input
  trigStateTwo = digitalRead(4); // read trigger input

  /////////////////////////////////////////////////////////////////////

  if (trigStateOne != lastTrigStateOne && trigStateOne == HIGH) {
    outOne = random(lowOne, highOne);
  }

  lastTrigStateOne = trigStateOne;

  /////////////////////////////////////////////////////////////////////

  if (trigStateTwo != lastTrigStateTwo && trigStateTwo == HIGH) {
    outTwo = random(lowTwo, highTwo);
  }

  lastTrigStateTwo = trigStateTwo;

  /////////////////////////////////////////////////////////////////////

  analogWrite(3, outOne);  // Print value to pin
  analogWrite(5, outTwo);  // Print value to pin

}
