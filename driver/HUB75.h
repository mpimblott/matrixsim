#ifndef HUB75_H
#define HUB75_H

#include <vector>
#include <bitset>
#include <iostream>

#include "../util.h"
#include "display.h"

enum PinState {
  HIGH = 1,
  LOW = 0
};

enum PinType {
  A,
  B,
  C,
  D,
  E,
  Latch,
  OE,
  R1,
  G1,
  B1,
  R2,
  G2,
  B2,
  CLK
};

struct Pin {
  PinType type;
  PinState state;
};

class HUB75Connector {
public:
  HUB75Connector(MatrixDisplay& display);
  void setPin(PinType type, PinState state);
  PinState readPin(PinType type);
  void print();

private:
  MatrixDisplay& display;
  std::bitset<WIDTH> RReg1;
  std::bitset<WIDTH> GReg1;
  std::bitset<WIDTH> BReg1;
  std::bitset<WIDTH> RReg2;
  std::bitset<WIDTH> GReg2;
  std::bitset<WIDTH> BReg2;
  std::vector<Pin> pinStates;
  void clockHigh();
  bool bufferReady = false;
  void latchHigh();
  void latchLow();
  int getRow();
};

#endif