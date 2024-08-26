  #include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Keypad.h>
#include <SoftwareSerial.h>
 
#define SERVO_PIN 11
#define SERVO_POZYCJA_ZAMKNIETY 20
#define SERVO_POZYCJA_OTWARTY 90
#define BT_RX_PIN 10  
#define BT_TX_PIN 9 
 
Servo lockServo;
LiquidCrystal_I2C lcd(0x27, 20, 4);
SoftwareSerial bluetooth(BT_RX_PIN, BT_TX_PIN);
 
 
const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 4;
byte rowPins[KEYPAD_ROWS] = {5, 4, 3, 2};
byte colPins[KEYPAD_COLS] = {A3, A2, A1, A0};
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);
 
String secretCode="5689";
String userCode="4321";
bool unlocked=false;
 
 
String inputSecretCode() {
  lcd.setCursor(5, 1);
  lcd.print("[____]");
  lcd.setCursor(6, 1);
  String result = "";
  while (result.length() < 4) {
    char key = keypad.getKey();
    if (key >= '0' && key <= '9') {
      lcd.print('*');
      result += key;
    }
  }
  return result;
}
 
void showWaitScreen(int delayMillis) {
  lcd.setCursor(2, 1);
  lcd.print("[..........]");
  lcd.setCursor(3, 1);
  for (byte i = 0; i < 10; i++) {
    delay(delayMillis);
    lcd.print("=");
  }
}
 
 
void showUnlockMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.setCursor(4, 0);
  lcd.print("Otwarty!");
  lcd.setCursor(15, 0);
  delay(1000);
}
 
bool setNewCode() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Wprowadz kod:");
  String newCode = inputSecretCode();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Potwierdz kod:");
  String confirmCode = inputSecretCode();
  if (newCode.equals(confirmCode)) {
    secretCode=newCode;
    return true;
  } else {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Kody nie pasuja!");
    lcd.setCursor(0, 1);
    lcd.print("Sejf otwarty!");
    delay(2000);
    return false;
  }
}
 
void safeLockedLogic() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Sejf zamkniety! ");
  String userCode = inputSecretCode();
  if (userCode==secretCode) {unlocked = unlock();}
  showWaitScreen(200);
  if (unlocked) {
    showUnlockMessage();
    unlock();
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dostep zabroniony!");
    showWaitScreen(1000);
  }
}
 
void safeUnlockedLogic() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Wybierz znak #");
  lcd.setCursor(0, 1);
  lcd.print("i podaj kod");
  lcd.setCursor(15, 0);
  bool newCodeNeeded = true;
  auto key = keypad.getKey();
  while (key != 'A' && key != '#') {
    key = keypad.getKey();
  }
  bool readyToLock = true;
  if (key == 'A' || newCodeNeeded) {
    readyToLock = setNewCode();
  }
  if (readyToLock) {
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print(" ");
    lcd.print("->");
    lcd.print(" ");
    lock();
    showWaitScreen(100);
  }
}
 
bool lock() {
  lockServo.write(SERVO_POZYCJA_ZAMKNIETY);
  unlocked=false;
  bluetooth.println("Sejf zamkniety!");
  return unlocked;
}
 
bool unlock() {
  lockServo.write(SERVO_POZYCJA_OTWARTY);
  unlocked=true;
  bluetooth.println("Sejf otwarty!");
  return unlock;
}
 
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("Sejf");
  lcd.begin(16, 2);
  lockServo.attach(SERVO_PIN);
  bluetooth.begin(9600);
  Serial.begin(115200);
  //lock();
  unlock();
 
}
 
void loop() {
  lcd.setCursor(1, 0);
  lcd.print("Sejf");
  lcd.setCursor(8, 1);
  lcd.print(millis() / 1000);
  if (!unlocked) {
    safeLockedLogic();
  } else {
    safeUnlockedLogic();
  }
}
 