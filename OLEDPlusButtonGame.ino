#define YPIN A0
#define XPIN A1
#define SWPIN 2
#define LDOWN 3
#define LUP 4
#define MID 5
#define RUP 7
#define RDOWN 6

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  pinMode(SWPIN, INPUT);
  digitalWrite(SWPIN, HIGH);
  pinMode(LDOWN, OUTPUT);
  pinMode(LUP, OUTPUT);
  pinMode(MID, OUTPUT);
  pinMode(RDOWN, OUTPUT);
  pinMode(RUP, OUTPUT);

  Serial.begin(115200);

  // Initialize the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.display(); // Display splash screen
  delay(2000);
  display.clearDisplay(); // Clear the buffer
}

void loop() {
  int przycisk = digitalRead(SWPIN);
  int osX = analogRead(XPIN);
  int osY = analogRead(YPIN);

  Serial.print("\nPrzycisk: ");
  Serial.println(przycisk);
  Serial.print("Oś X: ");
  Serial.println(osX);
  Serial.print("Oś Y: ");
  Serial.println(osY);
  Serial.print("\n\n ");

  display.clearDisplay(); // Clear the buffer before writing new text

  // Write text to display
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start drawing at coordinate (0,0)
  display.print("Przycisk: ");
  display.println(przycisk);
  display.print("Os X: ");
  display.println(osX);
  display.print("Os Y: ");
  display.println(osY);

  // Display what's been written to the display buffer
  display.display();

  if (przycisk == 0){
    digitalWrite(MID,HIGH);
  }
  else{
    digitalWrite(MID,LOW);
  }

  // lewy
  if (osX == 1023 and osY == 512){
    digitalWrite(RDOWN,HIGH);
  }
  else{
    digitalWrite(RDOWN,LOW);
  }

  //  gora
  if (osX == 512 and osY == 1023){
    digitalWrite(RUP,HIGH);
  }
  else{
    digitalWrite(RUP,LOW);
  }

  // prawy 
  if (osX == 0 and osY == 512){
    digitalWrite(LDOWN,HIGH);
  }
  else{
    digitalWrite(LDOWN,LOW);
  }

  //dol
  if (osX == 512 and osY == 0){
    digitalWrite(LUP,HIGH);
  }
  else{
    digitalWrite(LUP,LOW);
  }

  delay(1000);
}


// TRYB GRY
// #define YPIN A0
// #define XPIN A1
// #define SWPIN 2
// #define LDOWN 3
// #define LUP 4
// #define MID 5
// #define RUP 7
// #define RDOWN 6

// #define LED_PIN 8 

// #define SCREEN_WIDTH 128 
// #define SCREEN_HEIGHT 64 

// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

// #define OLED_RESET     -1 

// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// unsigned long lastChangeTime = 0;
// unsigned long lastButtonPressTime = 0;
// int points = 0;

// void setup() {
//   pinMode(SWPIN, INPUT);
//   digitalWrite(SWPIN, HIGH);
//   pinMode(LDOWN, OUTPUT);
//   pinMode(LUP, OUTPUT);
//   pinMode(MID, OUTPUT);
//   pinMode(RDOWN, OUTPUT);
//   pinMode(RUP, OUTPUT);
//   pinMode(LED_PIN, OUTPUT);

//   Serial.begin(115200);

//   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
//     Serial.println(F("SSD1306 allocation failed"));
//     for(;;);
//   }
//   display.display(); 
//   delay(2000);
//   display.clearDisplay(); 
// }

// void loop() {
//   int przycisk = digitalRead(SWPIN);
//   int osX = analogRead(XPIN);
//   int osY = analogRead(YPIN);

//   if (millis() - lastChangeTime >= 5000) { // Resetuj punkty po 5 sekundach
//     points = 0;
//     display.clearDisplay(); 
//     display.setTextSize(1);
//     display.setTextColor(SSD1306_WHITE);
//     display.setCursor(0, 0);
//     display.print("Punkty: ");
//     display.println(points);
//     display.display(); 
//     lastChangeTime = millis();
//   }

//   if (millis() - lastButtonPressTime >= 500 && (przycisk == LOW || osX == 0 || osX == 1023 || osY == 0 || osY == 1023)) {
//     points++; 
//     display.clearDisplay(); 
//     display.setTextSize(1);
//     display.setTextColor(SSD1306_WHITE);
//     display.setCursor(0, 0);
//     display.print("Punkty: ");
//     display.println(points);
//     display.display(); 
//     lastButtonPressTime = millis();
//   }

//   delay(50); 
// }