#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

double cm;
double cale;

void changeRGBColor(int redValue, int greenValue, int blueValue) {
  const int redPin = 10;   // Red pin
  const int greenPin = 9;  // Green pin
  const int bluePin = 8;   // Blue pin

  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void setup() {
  pinMode(8, OUTPUT); // Blue pin
  pinMode(9, OUTPUT); // Green pin
  pinMode(10, OUTPUT); // Red pin

  lcd.init();
  lcd.backlight();
  lcd.print("--> Odleglosc <--");
  delay(3000);
  lcd.clear();
}

void loop() {
  cm = 0.0344 / 2 * readUltrasonicDistance(3, 2);
  cale = (cm / 2.54);

  if (cm > 80) {
    // Zielony
    changeRGBColor(255, 0,255);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Green");
  } else if (cm > 40 && cm <= 80) {
    // Żółty
    changeRGBColor(0, 0, 255);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Yellow");
  } else if (cm <= 40 && cm > 0) {
    // Czerwony
    changeRGBColor(0, 255, 255);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Red");
  } else {
    // Wyłącz diody
    changeRGBColor(0, 0, 0);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Out of range");
  }

  lcd.setCursor(0, 1);
  lcd.print("Cale: ");
  lcd.print(cale, 1);
  lcd.setCursor(0, 2);
  lcd.print("Cm: ");
  lcd.print(cm, 1);
  delay(2000);
}