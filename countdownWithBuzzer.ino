#include "SevSeg.h"

SevSeg sevseg;
unsigned long previousMillis = 0; 
long interval = 1000; 
unsigned long timer = 100; 
bool timerRunning = false;
int lastPotValue = -1;

int numberOfSeconds(unsigned long time) {
  return time % 60; 
}

int numberOfMinutes(unsigned long time) {
  return (time / 60) % 60; 
}

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false;
  byte hardwareConfig = COMMON_ANODE;
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(10); 
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT); 
  pinMode(A3, OUTPUT);
  pinMode(A5, INPUT);
}

void loop() {
  int potValue = analogRead(A5);
  if (abs(potValue - lastPotValue) > 10) { 
    timer = map(potValue, 0, 1023, 1, 600);
    lastPotValue = potValue;
    timerRunning = true;
  }

  if (timerRunning) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(A2, HIGH); 
      delay(50);
      digitalWrite(A2, LOW);
      
      if (timer > 0) {
        timer--;
      } else {
        timerRunning = false;
        soundAlarm();
        signalEnd();
      }
    }
    printTimer();
  }
  delay(10);
}

void printTimer() {
  int minutes = numberOfMinutes(timer); 
  int seconds = numberOfSeconds(timer); 
  sevseg.setNumber(minutes * 100 + seconds, 2);
  sevseg.refreshDisplay(); 
}

void soundAlarm() {
  digitalWrite(A1, HIGH);
  delay(3000);
  digitalWrite(A1, LOW);
}

void signalEnd() {
  digitalWrite(A3, HIGH);
  delay(3000);
  digitalWrite(A3, LOW);
}