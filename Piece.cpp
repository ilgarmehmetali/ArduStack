
#include "Piece.h"

Piece::Piece(Adafruit_8x16matrix* matrix, TetrisMap* tetrisMap) {
  this->matrix = matrix;
  this->tetrisMap = tetrisMap;
}

void Piece::update() {

  aktifPosY++;
}

void Piece::draw() {

  //matrix->drawBitmap(aktifPosX, aktifPosY, image, width, height, LED_ON);
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (isCoordinateFull(x, y))
        if (y + aktifPosY >= 0)
          matrix->drawPixel(x + aktifPosX, y + aktifPosY, LED_ON);
    }
  }
}

bool Piece::isBitSet(byte b, int bit) {
  if ( 1 == ((b >> (bit)) & 1) )
    return true;
  return false;
}

bool Piece::isCoordinateFull(int x, int y) {
  return isBitSet(images[activeImage][y], 7 - x);
}

void Piece::slide(int direction) {
  int newPosX = aktifPosX + direction;

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (isCoordinateFull(x, y)) {

        if (y + aktifPosY >= 0)
          if (this->tetrisMap->isCoordinateFull(x + newPosX, y + aktifPosY)) {
            Serial.println("degiyor");
            return;
          }
        if ((x + newPosX) > 7) {
          return;
        }
        if ((x + newPosX) < 0) {
          return;
        }

      }
    }
  }
  aktifPosX = newPosX;
}

void Piece::rotate() {
  activeImage += 5;
  activeImage %= 4;

  if(checkCollisionWithTetrisMap()){
    activeImage += 3; // -1 +4
    activeImage %= 4;
    return;
  }

  if(isAnyPartOutofTetrisMap()){
    if(aktifPosX < 4){
      aktifPosX++;
    } else{
      aktifPosX--;
    }
    if(checkCollisionWithTetrisMap() || isAnyPartOutofTetrisMap()){
      if(aktifPosX < 4){
        aktifPosX--;
      } else{
        aktifPosX++;
      }
      activeImage += 3; // -1 +4
      activeImage %= 4;
    }
  }
}

bool Piece::checkCollisionWithTetrisMap(){
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (isCoordinateFull(x, y)) {
        if (this->tetrisMap->isCoordinateFull(x + aktifPosX, y + aktifPosY)) {
          return true;
        }
      }
    }
  }
  return false;
}

bool Piece::isAnyPartOutofTetrisMap(){
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (isCoordinateFull(x, y)) {
        if(x+aktifPosX < 0 || x+aktifPosX > 7 || y+aktifPosY > 15){
          return true;
        }
      }
    }
  }
  return false;
}

bool Piece::checkCollisionForNextStep() {
  aktifPosY++;
  bool collision = checkCollisionWithTetrisMap() || isAnyPartOutofTetrisMap();
  aktifPosY--;
  return collision;
}


