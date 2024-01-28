
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const int starterPin = 2;
const int sensorPin = 3;
const int buttonPin = 4;

const int READY = 1;
const int RUNNING = 2;
const int FINISHED = 3;

volatile int raceState = READY;
int buttonState = 0;

volatile unsigned long startTime = 0;
volatile unsigned long endTime = 0;
float duration = 0;

void setup() {

  lcd.begin(16, 2);

  lcd.print("Ready!");

  pinMode(buttonPin, INPUT);
  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(starterPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(starterPin), startRace, HIGH);
  attachInterrupt(digitalPinToInterrupt(sensorPin), finishRace, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (raceState != READY) {
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
      raceState = READY;
      // reset the timer
      startTime = 0;
      endTime = 0;
      duration = 0;
      lcd.print("Ready!");
    }
  }

  if (raceState == FINISHED) {
    // calculate the time
    duration = (endTime - startTime) / 1000000;

    // print the results to the screen
    lcd.print(duration);
  }
}

void startRace() {
  if (raceState == READY) {
    //start the timer
    startTime = micros();
    raceState = RUNNING;
  }
}

void finishRace() {
  if (raceState = RUNNING) {
    // stop the timer
    endTime = micros();
    raceState = FINISHED;
  }
}
