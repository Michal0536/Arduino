#include <IRremote.h>
#include <LiquidCrystal_I2C.h>
#define I2C_ADDR 0x27
#define LCD_COLUMNS 16
#define LCD_LINES 2
#define PIN_RECEIVER 2 // Sygnał Pin odbiornika podczerwieni (IR)
IRrecv receiver(PIN_RECEIVER);
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

String status = "off";

const int ledCount = 10; 

int ledOn = 0;

int ledPins[] = {
  4,5,6,7,8,9,10,11,12,13
};

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  
  receiver.enableIRIn(); // Uruchomienie odbiornika
  pinMode(8, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(0, OUTPUT);

  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  }
}

void loop()
{
  // Sprawdź odebrany sygnał IR

  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    // if the array element's index is less than ledLevel,
    // turn the pin for this element on:
    if (thisLed < ledOn) {
      digitalWrite(ledPins[thisLed], HIGH);
    }
    // turn off all pins higher than the ledLevel:
    else {
      digitalWrite(ledPins[thisLed], LOW);
    }
  }

  if (status == "off") {
    digitalWrite(1, HIGH);
    digitalWrite(0, LOW);
    ledOn = 0;
    lcd.begin(16, 2);
    lcd.print("Wlacz urzadzenie");
    if (receiver.decode() && receiver.decodedIRData.command == 162) {
      translateIR();
      receiver.resume();
    } else {
      receiver.resume();
    }
  } else {
    digitalWrite(0, LOW);
    digitalWrite(1, HIGH);

    if (receiver.decode()) {
      translateIR();
      receiver.resume(); // Odbierz kolejną wartość
    }
  }
  
}

void playSound(int frequency, int duration)
{
  for (int i = 0; i < duration * 1000 / (frequency * 2); i++) {
    digitalWrite(3, HIGH); // Włącz buzzer
    delayMicroseconds(frequency);    // Poczekaj przez połowę okresu
    digitalWrite(3, LOW);  // Wyłącz buzzer
    delayMicroseconds(frequency);    // Poczekaj przez połowę okresu
  }
  delay(10); // Dodaj trochę dodatkowego czasu dla płynniejszego odtwarzania dźwięku
}

void lcdPrint(char* text)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Wybrano przycisk:");
  lcd.setCursor(0, 1);
  lcd.print(text);
  lcd.print(" kod:");
  lcd.print(receiver.decodedIRData.command);
}

void translateIR()
{
  // Polecenia na podstawie otrzymanego kodu IR
  switch (receiver.decodedIRData.command) {
    case 162:
      lcdPrint("ZASILANIE");
      if (status == "off") {
        status = "on";
      } else {
        status = "off";
      }
      break;
    case 226:
      lcdPrint("MENU");
      break;
    case 34:
      lcdPrint("TEST");
      break;
    case 2:
      lcdPrint("PLUS");
      ledOn++;
      break;
    case 194:
      lcdPrint("WSTECZ");
      break;
    case 224:
      lcdPrint("POPRZEDNI");
      break;
    case 168:
      lcdPrint("PLAY");
      break;
    case 144:
      lcdPrint("NASTEPNY");
      break;
    case 104:
      lcdPrint("cyfra:0");
      break;
    case 152:
      lcdPrint("MINUS");
      ledOn--;
      break;
    case 176:
      lcdPrint("Litera:C");
      break;
    case 48:
      lcdPrint("cyfra:1");
      playSound(290, 20);
      break;
    case 24:
      lcdPrint("cyfra:2");
      playSound(300, 20);
      break;
    case 122:
      lcdPrint("cyfra:3");
      playSound(320, 20);
      break;
    case 16:
      lcdPrint("cyfra:4");
      playSound(340, 20);
      break;
    case 56:
      lcdPrint("cyfra:5");
      playSound(350, 20);
      break;
    case 90:
      lcdPrint("cyfra:6");
      playSound(360, 20);
      break;
    case 66:
      lcdPrint("cyfra:7");
      playSound(380, 20);
      break;
    case 74:
      lcdPrint("cyfra:8");
      playSound(400, 20);
      break;
    case 82:
      lcdPrint("cyfra:9");
      playSound(420, 20);
      break;
    default:
      lcd.clear();
      lcd.print(receiver.decodedIRData.command);
      lcd.print(" inny przycisk");
  }
}