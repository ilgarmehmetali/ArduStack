
#include "TetrisMap.h"


TetrisMap::TetrisMap(Adafruit_8x16matrix* matrix) {
  this->matrix = matrix;
}

void TetrisMap::draw() {
  for (int y = 0; y < 16; y++) {
    for (int x = 0; x < 8; x++) {
      if (isCoordinateFull(x, y)) {
        matrix->drawPixel(x, y, LED_ON);
      }
    }
  }
}


int TetrisMap::addPiecetoMap(Piece* piece) {
  for (int y = 0; y < piece->height; y++) {
    for (int x = 0; x < piece->width; x++) {
      if (piece->isCoordinateFull(x, y)) {
        setCoordinate(x + piece->aktifPosX, y + piece->aktifPosY, true);
      }
    }
  }
  return clearLines();
}

int TetrisMap::clearLines() {
  int sayac = 0;
  int lineBottom = -1, lineTop = -1;
  for (int y = 15; y > 0 ; y--) {
    sayac = 0;
    for (int x = 0; x < 8; x++) {
      if (isCoordinateFull(x, y)) {
        sayac++;
      }
    }
    if (sayac == 8) {
      if (lineBottom == -1) {
        lineBottom = y;
        lineTop = y;
      } else {
        lineTop = y;
      }
    }
  }
  int linesToRemove = lineBottom - (lineTop - 1);


  if (lineBottom != -1) {

    draw();
    for (int i = 0; i < 2; i++) {
      matrix->drawRect(0, lineTop, 8, linesToRemove, LED_OFF);
      matrix->writeDisplay();
      delay(200);
      matrix->drawRect(0, lineTop, 8, linesToRemove, LED_ON);
      matrix->writeDisplay();
      delay(200);
    }
    matrix->clear();

    for (int y = lineBottom; y > 0 ; y--) {
      for (int x = 0; x < 8; x++) {
        setCoordinate(x, y, isCoordinateFull(x, y - linesToRemove));
      }
    }
    for (int x = 0; x < 8; x++) {
      setCoordinate(x, 0, false);
    }
    return linesToRemove;
  }
  return 0;
}

bool TetrisMap::isGameOver() {
  for (int x = 0; x < 8; x++) {
    if (isCoordinateFull(x, 0)) {
      return true;
    }
  }


}

void TetrisMap::setCoordinate(int x, int y, bool value) {
  if (isCoordinateFull(x, y)) {
    if (value) {
      return;
    } else {
      mapData[y] = flipBit(mapData[y], 7 - x);
    }
  } else {
    if (value) {
      mapData[y] = flipBit(mapData[y], 7 - x);
    } else {
      return;
    }
  }
}

byte TetrisMap::flipBit(byte b, int bit ) {
  bool isBitSet = ( 1 == ((b >> (bit)) & 1) );
  byte mask = 1 << bit;
  if (isBitSet) {
    return (b ^ mask);
  } else {
    return (b | mask);
  }
}

bool TetrisMap::isBitSet(byte b, int bit) {
  if ( 1 == ((b >> (bit)) & 1) )
    return true;
  return false;
}

bool TetrisMap::isCoordinateFull(int x, int y) {
  if (y < 0) {
    return false;
  }
  return isBitSet(mapData[y], 7 - x);
}

