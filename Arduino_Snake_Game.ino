/*
===========================================================
 PROJECT TITLE  : Arduino Snake Game (Nokia Style)

 DESCRIPTION:
 A classic Snake game inspired by old Nokia phones,
 built using an 8x8 LED Matrix (MAX7219).

 The snake is controlled using a KY-023 joystick,
 and a buzzer is used to provide sound effects for
 movement, eating food, and game over events.

 This project is beginner-friendly and perfect for
 learning Arduino game logic, display control, and
 input handling.

===========================================================
 FEATURES:
 - Smooth snake movement
 - Screen wrapping (no walls, classic style)
 - Food spawning system
 - Snake grows when eating food
 - Self-collision detection (Game Over)
 - Sound effects:
    • Movement beep (short tick)
    • Eat sound (higher tone reward)
    • Game over sound (descending tone)
 - Game Over animation:
    • Explosion effect
    • Big "X" display

===========================================================
 COMPONENTS REQUIRED:
 - Arduino UNO / Nano
 - MAX7219 8x8 LED Matrix Module
 - KY-023 Joystick Module
 - Buzzer (Active or Passive)
 - Jumper Wires

===========================================================
 WIRING CONNECTIONS:

 MAX7219 LED Matrix:
   VCC  -> 5V
   GND  -> GND
   DIN  -> D11
   CS   -> D10
   CLK  -> D13

 Joystick KY-023:
   VRx  -> A0
   VRy  -> A1
   SW   -> D2 (optional, not used)
   VCC  -> 5V
   GND  -> GND

 Buzzer:
   (+)  -> D3
   (-)  -> GND

===========================================================
 LIBRARIES REQUIRED:
 - MD_MAX72XX by MajicDesigns
 - SPI (built-in)

 Install via Arduino Library Manager.

===========================================================
*/

// ================= LIBRARIES =================
#include <MD_MAX72xx.h>
#include <SPI.h>

// ================= MAX7219 CONFIG =================
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES   1

#define DATA_PIN 11
#define CLK_PIN  13
#define CS_PIN   10

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN);

// ================= PIN CONFIG =================
#define JOY_X   A0
#define JOY_Y   A1
#define BUZZER  3

// ================= GAME CONFIG =================
const int GRID_SIZE  = 8;
const int MAX_LENGTH = 64;

int snakeX[MAX_LENGTH];
int snakeY[MAX_LENGTH];
int snakeLength = 3;

int dirX = 1; // initial direction (right)
int dirY = 0;

int foodX, foodY;

bool isGameOver = false;

unsigned long lastMoveTime = 0;
int moveInterval = 250; // speed control

// ===========================================================
// SETUP FUNCTION
// ===========================================================
void setup() {
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 5);
  mx.clear();

  pinMode(BUZZER, OUTPUT);

  randomSeed(analogRead(0));

  resetGame();
}

// ===========================================================
// MAIN LOOP
// ===========================================================
void loop() {
  if (isGameOver) {
    showGameOverScreen();
    delay(2000);
    resetGame();
    return;
  }

  readJoystick();

  // control movement speed
  if (millis() - lastMoveTime > moveInterval) {
    updateSnake();
    lastMoveTime = millis();
  }

  renderDisplay();
}

// ===========================================================
// RESET GAME STATE
// ===========================================================
void resetGame() {
  snakeLength = 3;

  // initial position
  snakeX[0] = 3; snakeY[0] = 3;
  snakeX[1] = 2; snakeY[1] = 3;
  snakeX[2] = 1; snakeY[2] = 3;

  dirX = 1;
  dirY = 0;

  spawnFood();
  isGameOver = false;
}

// ===========================================================
// SPAWN FOOD
// ===========================================================
void spawnFood() {
  foodX = random(0, GRID_SIZE);
  foodY = random(0, GRID_SIZE);
}

// ===========================================================
// JOYSTICK CONFIGURATION (PRO STYLE)
// Adjust these values if your joystick direction feels reversed
//
// 1  = Normal direction
// -1 = Inverted direction
// ===========================================================
int invertX = 1; // change to -1 if LEFT/RIGHT feels correct
int invertY = -1; // change to 1 if UP/DOWN feels correct


// ===========================================================
// READ JOYSTICK INPUT
// Flexible control using invert variables
// ===========================================================
void readJoystick() {
  int x = analogRead(JOY_X);
  int y = analogRead(JOY_Y);

  // ==============================
  // HORIZONTAL MOVEMENT (X AXIS)
  // ==============================
  if (x < 300 && dirX == 0) {
    dirX = -1 * invertX;
    dirY = 0;
  } 
  else if (x > 700 && dirX == 0) {
    dirX = 1 * invertX;
    dirY = 0;
  }

  // ==============================
  // VERTICAL MOVEMENT (Y AXIS)
  // ==============================
  if (y < 300 && dirY == 0) {
    dirX = 0;
    dirY = -1 * invertY;
  } 
  else if (y > 700 && dirY == 0) {
    dirX = 0;
    dirY = 1 * invertY;
  }
}

// ===========================================================
// SOUND EFFECTS
// ===========================================================

// movement sound (short tick)
void playMoveSound() {
  tone(BUZZER, 1200, 15);
}

// eating sound (reward tone)
void playEatSound() {
  tone(BUZZER, 1500, 80);
  delay(80);
  tone(BUZZER, 1800, 100);
}

// game over sound (descending tone)
void playGameOverSound() {
  for (int freq = 800; freq >= 300; freq -= 50) {
    tone(BUZZER, freq, 50);
    delay(50);
  }
}

// ===========================================================
// UPDATE SNAKE LOGIC
// ===========================================================
void updateSnake() {
  playMoveSound(); // sound each movement

  int newX = snakeX[0] + dirX;
  int newY = snakeY[0] + dirY;

  // screen wrapping
  if (newX < 0) newX = 7;
  if (newX > 7) newX = 0;
  if (newY < 0) newY = 7;
  if (newY > 7) newY = 0;

  // self collision detection
  for (int i = 0; i < snakeLength; i++) {
    if (snakeX[i] == newX && snakeY[i] == newY) {
      isGameOver = true;
      return;
    }
  }

  // move body
  for (int i = snakeLength; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  // update head
  snakeX[0] = newX;
  snakeY[0] = newY;

  // check food
  if (newX == foodX && newY == foodY) {
    snakeLength++;
    playEatSound();
    spawnFood();
  }
}

// ===========================================================
// RENDER DISPLAY
// ===========================================================
void renderDisplay() {
  mx.clear();

  // draw snake
  for (int i = 0; i < snakeLength; i++) {
    mx.setPoint(snakeY[i], snakeX[i], true);
  }

  // draw food
  mx.setPoint(foodY, foodX, true);

  mx.update();
}

// ===========================================================
// GAME OVER SCREEN + ANIMATION
// ===========================================================
void showGameOverScreen() {
  playGameOverSound();

  byte frame1[8] = {
    B00000000,
    B00100100,
    B00011000,
    B00111100,
    B00111100,
    B00011000,
    B00100100,
    B00000000
  };

  byte frame2[8] = {
    B00100100,
    B00000000,
    B01111110,
    B00111100,
    B00111100,
    B01111110,
    B00000000,
    B00100100
  };

  byte Xpattern[8] = {
    B10000001,
    B01000010,
    B00100100,
    B00011000,
    B00011000,
    B00100100,
    B01000010,
    B10000001
  };

  // explosion animation
  for (int i = 0; i < 8; i++) mx.setRow(i, frame1[i]);
  mx.update();
  delay(150);

  for (int i = 0; i < 8; i++) mx.setRow(i, frame2[i]);
  mx.update();
  delay(150);

  // show big X
  for (int i = 0; i < 8; i++) mx.setRow(i, Xpattern[i]);
  mx.update();
}