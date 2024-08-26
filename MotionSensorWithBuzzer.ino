#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 
#define OLED_ADDR 0x3C
#define OLED_RESET     -1 // No reset pin used


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


int ledPin = 13; // Pin dla diody LED
int inputPin = 2; // wejście dla czujnika ruchu PIR
int buzzerPin = 9; // Pin for the buzzer
int pirState = LOW; // stan początkowy czujnika (brak ruchu)
int val = 0; 


void setup() {
  pinMode(ledPin, OUTPUT); // zadeklarowanie diody LED jako wyjścia
  pinMode(inputPin, INPUT); // zadeklarowanie czujnika jako wejścia
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
  Serial.println(F("SSD1306 allocation failed"));
  for(;;); 
  }

  display.display();
  delay(2000); 
  display.clearDisplay();
  display.setTextSize(1); 
  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(0,0); 
  display.cp437(true); 
}

void loop() {
  val = digitalRead(inputPin); // odczytaj wartość na wejściu
  if (val == HIGH) { // na wejściu jest stan wysoki HIGH
    digitalWrite(ledPin, HIGH); // zapal diodę LED
    if (pirState == LOW) {
      Serial.println("Wykryto ruch!");
      tone(buzzerPin, 1000, 200);
      display.clearDisplay();
      display.setCursor(0,0);
      display.println(F("Wykryto ruch!"));
      display.display();
      pirState = HIGH;
    }
  } else {
  digitalWrite(ledPin, LOW); // wyłącz diodę LED
    if (pirState == HIGH) {
    Serial.println("Nie wykryto ruchu.");
    noTone(buzzerPin);
    display.clearDisplay();
    display.setCursor(0,0);
    display.println(F("Nie wykryto ruchu."));
    display.display();
    pirState = LOW;
  }
  }
}