#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_ADDR 0x3C
#define OLED_SDA A5
#define OLED_SCL A4
#define JOY_X A1
#define JOY_Y A0
#define JOY_PIN 3  // Zmieniono na pin 3
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SNAKE_SIZE 4
#define MAX_SNAKE_SIZE 100
#define BUZZER_PIN 6  // Definiowanie pinu dla buzzera

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_ADDR);

int snakeX[MAX_SNAKE_SIZE];
int snakeY[MAX_SNAKE_SIZE];
int snakeSize = SNAKE_SIZE;
int snakeDir = 1;
int foodX = 1, foodY = 1;
bool gameOver = false;
bool isPaused = false;
int score = 0;
unsigned long buttonPressedTime = 0;
bool isButtonPressed = false;

void playSound(int note, int duration) {
  tone(BUZZER_PIN, note, duration);
  delay(duration);
  noTone(BUZZER_PIN);
}

void initSnake() {
  int startX = SCREEN_WIDTH / 2;
  int startY = SCREEN_HEIGHT / 2;
  for (int i = 0; i < snakeSize; i++) {
    snakeX[i] = startX - i;
    snakeY[i] = startY;
  }
  foodX = random(0, SCREEN_WIDTH);
  foodY = random(0, SCREEN_HEIGHT);
  score = 0;
}

void updateSnake() {
  if (isPaused) return;

  int newHeadX = snakeX[0];
  int newHeadY = snakeY[0];

  switch (snakeDir) {
    case 0: newHeadY--; break;
    case 1: newHeadX++; break;
    case 2: newHeadY++; break;
    case 3: newHeadX--; break;
  }

  if (newHeadX < 0 || newHeadX >= SCREEN_WIDTH || newHeadY < 0 || newHeadY >= SCREEN_HEIGHT) {
    gameOver = true;
    playSound(200, 500);  // Dźwięk game over
    return;
  }

  for (int i = 1; i < snakeSize; i++) {
    if (newHeadX == snakeX[i] && newHeadY == snakeY[i]) {
      gameOver = true;
      playSound(200, 500);  // Dźwięk game over
      return;
    }
  }

  if (newHeadX == foodX && newHeadY == foodY) {
    snakeSize++;
    score++;
    playSound(1000, 100);  // Dźwięk zbierania pokarmu
    if (snakeSize > MAX_SNAKE_SIZE) {
      snakeSize = MAX_SNAKE_SIZE;
    }
    foodX = random(0, SCREEN_WIDTH);
    foodY = random(0, SCREEN_HEIGHT);
  } else {
    for (int i = snakeSize - 1; i > 0; i--) {
      snakeX[i] = snakeX[i - 1];
      snakeY[i] = snakeY[i - 1];
    }
  }
  snakeX[0] = newHeadX;
  snakeY[0] = newHeadY;
}

void drawGame() {
  display.clearDisplay();
  for (int i = 0; i < snakeSize; i++) {
    display.fillRect(snakeX[i], snakeY[i], 4, 4, WHITE);
  }
  display.fillRect(foodX, foodY, 4, 4, WHITE);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Score: ");
  display.println(score);

  display.display();
}

void checkButtonPress() {
  int joyPinState = digitalRead(JOY_PIN);
  if (joyPinState == LOW && !isButtonPressed) {
    isButtonPressed = true;
    buttonPressedTime = millis();
  } else if (joyPinState == HIGH && isButtonPressed) {
    if ((millis() - buttonPressedTime) > 1000) {
      gameOver = false;
      initSnake();
    } else {
      isPaused = !isPaused;
    }
    isButtonPressed = false;
  }
}

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  randomSeed(A0);
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(20, 10);
  display.println("Snake Game");
  display.display();
  pinMode(JOY_X, INPUT);
  pinMode(JOY_Y, INPUT);
  pinMode(JOY_PIN, INPUT_PULLUP);
  delay(2000);
  initSnake();
}

void loop() {
  checkButtonPress();

  if (!gameOver) {
    if (!isPaused) {
      updateSnake();
      drawGame();
      int joyX = analogRead(JOY_X);
      int joyY = analogRead(JOY_Y);
      if (joyX < 100) snakeDir = 1;
      else if (joyX > 900) snakeDir = 3;
      else if (joyY < 100) snakeDir = 2;
      else if (joyY > 900) snakeDir = 0;

      delay(20);
    }
  } else {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(10, SCREEN_HEIGHT / 2 - 10);
    display.print("Game Over");
    display.setTextSize(1);
    display.setCursor(10, SCREEN_HEIGHT / 2 + 20);
    display.print("Score: ");
    display.println(score);
    display.display();
    while (true) {}
  }
}