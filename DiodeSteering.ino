void setup() {
pinMode(2, OUTPUT); // pin sterujący pierwszą diodą LED jest ustawiany
// jako wyjściowy
pinMode(3, OUTPUT); // to samo należy zrobić dla diod LED od 2 do 5
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
}

// void loop() {
// digitalWrite(2, HIGH); // włącza 1 diodę LED
// delay(500); // oczekiwanie 0.5 sekundy
// digitalWrite(2, LOW); // wyłącza 2 diodę LED
// digitalWrite(3, HIGH); // w ten sam sposób włączane i wyłaczane są diody LED od 2
// //do 5
// delay(500);
// digitalWrite(3, LOW);
// digitalWrite(4, HIGH);
// delay(500);
// digitalWrite(4, LOW);
// digitalWrite(5, HIGH);
// delay(500);
// digitalWrite(5, LOW);
// digitalWrite(6, HIGH);
// delay(500);
// digitalWrite(6, LOW);
// digitalWrite(5, HIGH);
// delay(500);
// digitalWrite(5, LOW);
// digitalWrite(4, HIGH);
// delay(500);
// digitalWrite(4, LOW);
// digitalWrite(3, HIGH);
// delay(500);
// digitalWrite(3, LOW);
// }

void loop(){
  for (int i = 2; i<7;i++){
    digitalWrite(i, HIGH);
    delay(500);
    digitalWrite(i,LOW);
  }
  for (int i = 7; i>2;i--){
    digitalWrite(i, HIGH);
    delay(500);
    digitalWrite(i,LOW);
  }
  
}