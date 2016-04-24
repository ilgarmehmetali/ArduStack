
#ifndef PieceTypes_h
#define PieceTypes_h

#include "Arduino.h"

const uint8_t PieceT0[4] = {
  B00100000,
  B01110000,
  B00000000,
  B00000000
};

const uint8_t PieceT1[4] = {
  B00100000,
  B00110000,
  B00100000,
  B00000000
};

const uint8_t PieceT2[4] = {
  B00000000,
  B01110000,
  B00100000,
  B00000000
};

const uint8_t PieceT3[4] = {
  B00100000,
  B01100000,
  B00100000,
  B00000000
};

const uint8_t PieceB0[4] = {
  B00000000,
  B01100000,
  B01100000,
  B00000000
};

const uint8_t PieceS0[4] = {
  B00100000,
  B00110000,
  B00010000,
  B00000000
};

const uint8_t PieceS1[4] = {
  B00000000,
  B00110000,
  B01100000,
  B00000000
};

const uint8_t PieceZ0[4] = {
  B00010000,
  B00110000,
  B00100000,
  B00000000
};

const uint8_t PieceZ1[4] = {
  B00000000,
  B01100000,
  B00110000,
  B00000000
};


const uint8_t PieceJ0[4] = {
  B01000000,
  B01110000,
  B00000000,  
  B00000000
};

const uint8_t PieceJ1[4] = {
  B00110000,
  B00100000,
  B00100000,
  B00000000  
};

const uint8_t PieceJ2[4] = {
  B00000000,  
  B01110000,
  B00010000,
  B00000000
};

const uint8_t PieceJ3[4] = {
  B00100000,  
  B00100000,
  B01100000,
  B00000000
};

const uint8_t PieceL0[4] = {
  B00000000,  
  B01110000,
  B01000000,
  B00000000
};

const uint8_t PieceL1[4] = {
  B01100000,
  B00100000,
  B00100000,
  B00000000  
};

const uint8_t PieceL2[4] = {
  B00010000,
  B01110000,
  B00000000, 
  B00000000
};

const uint8_t PieceL3[4] = {
  B00100000,  
  B00100000,
  B00110000,
  B00000000
};

const uint8_t PieceI0[4] = {
  B00100000,
  B00100000,
  B00100000,
  B00100000
};

const uint8_t PieceI1[4] = {
  B00000000,
  B11110000,
  B00000000,
  B00000000
};


extern const uint8_t** PieceTypes[7];


#endif PieceTypes_h
