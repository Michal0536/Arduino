#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2 
#define DHTTYPE DHT22 
#define LIGHT_SENSOR A0
#define RED_LED 3
#define YELLOW_LED 4
#define GREEN_LED 5

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adres I2C ekranu, liczba kolumn, liczba wierszy

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // Inicjalizacja ekranu LCD
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  
  dht.begin();

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  //printSensorDetails(sensor);

  dht.humidity().getSensor(&sensor);
  //printSensorDetails(sensor);

  delayMS = sensor.min_delay / 1000;
}

void loop() {
  delay(delayMS);

  sensors_event_t temperatureEvent, humidityEvent; // Deklaracja dwóch zmiennych wydarzeń

  dht.temperature().getEvent(&temperatureEvent); // Pobranie wydarzenia temperatury
  dht.humidity().getEvent(&humidityEvent); // Pobranie wydarzenia wilgotności

  // Obsługa diód LED
  if (!isnan(temperatureEvent.temperature) && !isnan(humidityEvent.relative_humidity)) {
    if (temperatureEvent.temperature > 30 || humidityEvent.relative_humidity > 80) {
      digitalWrite(RED_LED, HIGH); // Czerwona dioda: niebezpieczny zakres
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
    } else if (temperatureEvent.temperature > 25 || humidityEvent.relative_humidity > 70) {
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, HIGH); // Żółta dioda: ostrzeżenie
      digitalWrite(GREEN_LED, LOW);
    } else {
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, HIGH); // Zielona dioda: normalny zakres
    }
  }

  if (!isnan(temperatureEvent.temperature)) {
    Serial.print("Temperature: ");
    Serial.print(temperatureEvent.temperature);
    Serial.println("°C");
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperatureEvent.temperature);
    lcd.print("C");
  }

  if (!isnan(humidityEvent.relative_humidity)) { // Sprawdzenie czy wilgotność jest poprawna
    Serial.print("Humidity: ");
    Serial.print(humidityEvent.relative_humidity);
    Serial.println("%");
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(humidityEvent.relative_humidity);
    lcd.print("%");
  }

  int lightLevel = analogRead(LIGHT_SENSOR);
  Serial.print("Light Level: ");
  Serial.println(lightLevel);
  lcd.setCursor(0, 1);
  lcd.print("Light: ");
  lcd.print(lightLevel);
  lcd.print("   "); // Wyczyszczenie poprzednich danych
}

void printSensorDetails(sensor_t sensor) {
  Serial.println("Sensor details:");
  Serial.print("Name: ");
  Serial.println(sensor.name);
  Serial.print("Driver version: ");
  Serial.println(sensor.version);
  Serial.print("Sensor ID: ");
  Serial.println(sensor.sensor_id);
  Serial.print("Max value: ");
  Serial.print(sensor.max_value);
  //Serial.println(sensor.unit);
  Serial.print("Min value: ");
  Serial.print(sensor.min_value);
  //Serial.println(sensor.unit);
  Serial.print("Resolution: ");
  Serial.print(sensor.resolution);
  //Serial.println(sensor.unit);
  Serial.println("------------------------------------");
}