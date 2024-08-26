#define HOT 6
#define NORMAL 4
#define COLD 2
float celsius = 0;
float hotTemp = 26;
float coldTemp = 15;
const float BETA = 3950; // should match the Beta Coefficient of the thermistor

void setup() {
pinMode(HOT, OUTPUT);
pinMode(NORMAL, OUTPUT);
pinMode(COLD, OUTPUT);
Serial.begin(9600);
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
digitalWrite(COLD, HIGH);
delay(1000);
digitalWrite(COLD, LOW);
}
else if ( celsius > coldTemp && celsius <= hotTemp )
{
digitalWrite(NORMAL, HIGH);
delay(1000);
digitalWrite(NORMAL, LOW);
}
else
{
// celsius > hotTemp
digitalWrite(HOT, HIGH);
delay(1000);
digitalWrite(HOT, LOW);
}
}