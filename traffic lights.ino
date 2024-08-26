int redLED1 = 2; 
int yellowLED1 = 3; 
int greenLED1 = 4;  

int redLED2 = 5; 
int yellowLED2 = 6; 
int greenLED2 = 7;  

int button1 = 8; 
int button2 = 9; 

void setup() {
  pinMode(redLED1, OUTPUT);
  pinMode(yellowLED1, OUTPUT);
  pinMode(greenLED1, OUTPUT);
  
  pinMode(redLED2, OUTPUT);
  pinMode(yellowLED2, OUTPUT);
  pinMode(greenLED2, OUTPUT);

  pinMode(button1, INPUT_PULLUP); 
  pinMode(button2, INPUT_PULLUP); 
  
  digitalWrite(greenLED1, HIGH); 
  digitalWrite(redLED2, HIGH); 
}

void loop() {
  if (digitalRead(button1) == LOW) { 
    changeLights(redLED1, yellowLED1, greenLED1, redLED2, yellowLED2, greenLED2);
  }
  if (digitalRead(button2) == LOW) { 
    changeLights(redLED2, yellowLED2, greenLED2, redLED1, yellowLED1, greenLED1);
  }
}

void changeLights(int redLEDOff, int yellowLED, int greenLEDOn, int redLEDOn, int yellowLEDOff, int greenLEDOff) {
  digitalWrite(greenLEDOff, LOW);
  digitalWrite(yellowLED, HIGH);
  delay(2000); 
  
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLEDOff, LOW);
  digitalWrite(greenLEDOn, HIGH);
  digitalWrite(redLEDOn, HIGH);
  
  delay(5000); 
}