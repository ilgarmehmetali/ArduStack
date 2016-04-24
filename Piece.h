
#ifndef Piece_h
#define Piece_h

#include "PieceTypes.h"
#include "TetrisMap.h"

#include "Arduino.h"
#include "Adafruit_LEDBackpack.h"

class Piece {
  public:
    Piece(Adafruit_8x16matrix* matrix, TetrisMap* tetrisMap);
    void update();
    void draw();
    bool checkCollisionForNextStep();
    void slide(int direction);
    bool isBitSet(byte b, int bit);
    bool isCoordinateFull(int x, int y);
    void rotate();
    bool isAnyPartOutofTetrisMap();
    bool checkCollisionWithTetrisMap();


    int aktifPosX = 0;
    int aktifPosY = -3;
    int width = 4;
    int height = 4;
    int activeImage = 1;//random(0, 4);

    const uint8_t** images = PieceTypes[random(0,7)];

  protected:
    Adafruit_8x16matrix* matrix;
    TetrisMap* tetrisMap;

};

#endif
