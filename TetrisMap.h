
#ifndef TetrisMap_h
#define TetrisMap_h


#include "Arduino.h"
#include "Adafruit_LEDBackpack.h"

class Piece;

class TetrisMap {
  public:

    TetrisMap(Adafruit_8x16matrix* matrix);
    bool isCoordinateFull(int x, int y);
    bool isBitSet(byte b, int bit);
    void setCoordinate(int x, int y, bool value);
    bool isGameOver();
    byte flipBit(byte b, int bit);
    int addPiecetoMap(Piece* piece);
    void draw();
    void update();
    int clearLines();

  private:
  
    Adafruit_8x16matrix* matrix;

    uint8_t mapData[16] = {
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000
    };
};

#include "Piece.h"

#endif TetrisMap_h

