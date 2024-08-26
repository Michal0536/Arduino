// Arduino i wyświetlacz LCD1602
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 10, 9, 8, 7); // piny RS, E, DB4, DB5, DB6, DB7
// modułu LCD
void setup() {
lcd.begin(16, 2);
}
void loop() {
for (int i=0;i<16;++i) {
lcd.clear();
lcd.setCursor(i, 0);

lcd.print("Hello");
lcd.setCursor(i, 1);
lcd.print("World!");
delay(150);
}
}