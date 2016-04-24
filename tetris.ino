
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#include "Piece.h"
#include "TetrisMap.h"

int buttonLeft = 8;
int buttonRight = 9;
int buttonRotate = 11;

Adafruit_8x16matrix* matrix;
Piece* p;
TetrisMap* tetrisMap;

void(* reset) (void) = 0;

int delayAmountNormal = 300;
int delayAmountFast = 200;
int delayAmount;

int score = 0;
String scoreText;


void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(2));

  pinMode(buttonLeft, INPUT);
  pinMode(buttonRight, INPUT);
  pinMode(buttonRotate, INPUT);

  matrix = new Adafruit_8x16matrix();
  matrix->begin(0x70);  // pass in the address
  matrix->setBrightness(1);
  matrix->setRotation(0);

  tetrisMap = new TetrisMap(matrix);

  p = new Piece(matrix, tetrisMap);

  delayAmount = delayAmountNormal;
  scoreText = String(" Puan:");

}

int sonUpdate = 0;
void loop() {

  handleInput();
  matrix->clear();

  if ((millis() / delayAmount) > sonUpdate) {

    if (p->checkCollisionForNextStep()) {
      int removedLineCount = tetrisMap->addPiecetoMap(p);
      score+= int(pow(2, removedLineCount-1)) * 10;
      
      delete p;
      p = new Piece(matrix, tetrisMap);
    }

    p->update();

    if (tetrisMap->isGameOver()) {
      delay(1000);
      scoreText.concat(score);
      matrix->setTextSize(1);
      matrix->setTextWrap(false);
      matrix->setTextColor(LED_ON);
      for (int8_t x = 0; x >= -64; x--) {
        matrix->clear();
        matrix->setCursor(x, 5);
        matrix->print(scoreText);
        matrix->writeDisplay();
        delay(150);
      }
      blinkScreen(3);
      delay(1000);
      reset();
    }

    sonUpdate = millis() / delayAmount;

  }
  tetrisMap->draw();
  p->draw();

  matrix->writeDisplay();
  //delay(delayAmount);
}

int prevReadingLeft = LOW, prevReadingRight = LOW, prevReadingRotate = LOW;
int readingLeft, readingRight, readingRotate;

void handleInput() {
  readingLeft = digitalRead(buttonLeft);
  readingRight = digitalRead(buttonRight);
  readingRotate = digitalRead(buttonRotate);


  if (readingLeft != prevReadingLeft) {
    if (readingLeft == HIGH) {
      p->slide(-1);
    }
  }
  if (readingRight != prevReadingRight) {
    if (readingRight == HIGH) {
      p->slide(+1);
    }
  }
  if (readingRotate != prevReadingRotate) {
    if (readingRotate == HIGH) {
      p->rotate();
    }
  }

  prevReadingLeft = readingLeft;
  prevReadingRight = readingRight;
  prevReadingRotate = readingRotate;

}


void blinkScreen(int times) {
  for (int i = 0; i < times; i++) {
    matrix->fillScreen(0);
    matrix->writeDisplay();
    delay(300);
    matrix->fillScreen(1);
    matrix->writeDisplay();
    delay(300);
  }
}

