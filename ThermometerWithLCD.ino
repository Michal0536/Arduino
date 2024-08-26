#include <LiquidCrystal.h>
float celsius = 0;
float hotTemp = 26;
float coldTemp = 15;
const float BETA = 3950;
LiquidCrystal lcd(12, 11, 10, 9, 8, 7); // piny RS, E, DB4, DB5, DB6, DB7
// modułu LCD
void setup() {
Serial.begin(9600);
lcd.begin(16, 2);
}
void loop() {
// odczytuje stan czujnika temperatury i konwertuje wynik na stopnie Celsjusza
int analogValue = analogRead(A0);
// konwertuje miliwolty na stopnie Celsjusza
float celsius = 1 / (log(1 / (1023. / analogValue - 1)) / BETA + 1.0 / 298.15) -
273.15;
Serial.print("Temperatura: ");
Serial.print(celsius);
Serial.println(" ℃");
delay(1000);
// obsługa przedziałów temperatur:
if ( celsius < coldTemp )
{
lcd.clear();
lcd.print('goraco');

}
else if ( celsius > coldTemp && celsius <= hotTemp )
{
lcd.clear();
lcd.print('ok');
}
else
{
lcd.clear();  
lcd.print('zimno');
}
}