/*
  Circuit Description
  Connect 4 green leds and a white led to digital pins, add a resitor and connect to ground
  wire button from 5v to ground volt and attach to a digital pin
  add an RGB led to the circuit

  Chukwunonso Elumeze
  03/07/2021
*/
#include <millisDelay.h>
//The pin buttons for the leds
const int ledTwo = 2;
const int ledThree = 3;
const int ledCorrect = 4; //Led to aim for
const int ledFive = 5;
const int ledSix = 6;
int redPin = 8;
int greenPin = 10;
int bluePin = 11;
//delay values
int delay_Speed = 2000;
int delay_Result = 500;
const int button = 13; //button Pin
int buttonState;       //button state
int difficult = 1;     //difficulty
millisDelay testDelay;
// the setup function runs once when you press reset or power the board
void setup()
{
  // initialize the pins as output.
  pinMode(ledTwo, OUTPUT);
  pinMode(ledThree, OUTPUT);
  pinMode(ledCorrect, OUTPUT);
  pinMode(ledFive, OUTPUT);
  pinMode(ledSix, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(button, INPUT);
}
// the loop function runs over and over again forever
void loop()
{
  int amount = 2;
  while (amount < 7)
  {
    //displays the LED for each pin
    displayGame(amount);
    amount++;
  }
}

void setDifficulty(int state_Of_Difficulty)
{
  //sets the delay to a value depending on the level of the player
  delay_Speed = 2000 / state_Of_Difficulty;
}
void getButtonState()
{
  //gets the state of the button
  buttonState = digitalRead(button);
}
//if the button was clicked at the wrong time
void badInput()
{
  if (buttonState == HIGH)
  {
    failedTheLevel(); //display the LED that shows you failed
    if (difficult != 1)
      difficult = difficult - 1;    //reset the difficulty
  }
}
//if the button was clicked at the right time
void goodInput()
{
  if (buttonState == HIGH)
  {
    passedTheLevel();          //display the LED that shows you passed
    difficult = difficult + 1; //increase the difficulty
  }
}
//Switches an LED ON/OFF to show that you passed the level
void passedTheLevel()
{
  setColor(0, 255, 0);
  delay(delay_Result);
  setColor(0, 0, 0);
}
//Switches an LED ON/OFF to show that you failed the level
void failedTheLevel()
{ setColor(255, 0, 0);
  delay(delay_Result);
  setColor(0, 0, 0);
}
void displayGame(int ledTest)
{
  digitalWrite(ledTest, HIGH);
  testDelay.start(delay_Speed);
  while (testDelay.justFinished() == false)
  {
    getButtonState();
    if (ledTest != ledCorrect)
      badInput();
    else
      goodInput();
  };
  digitalWrite(ledTest, LOW);
  setDifficulty(difficult);
}
void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
