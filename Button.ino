#define LED 12
#define BUTTON 7
void setup()
{
pinMode(LED, OUTPUT); // pin wyjściowy dla diody LED
pinMode(BUTTON, INPUT); // pin wejściowy dla przycisku
}
void loop()
{
if ( digitalRead(BUTTON) == HIGH )
{
digitalWrite(LED, HIGH); // włącza diodę LED
delay(1000); // czeka jedną sekundę
digitalWrite(LED, LOW); // wyłącza diodę LED
}
}

