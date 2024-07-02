#include "HUB75.h"

HUB75Connector::HUB75Connector(MatrixDisplay& display) : display(display) {
  for (int i = 0; i < 13; i++) {
    Pin pin;
    pin.type = static_cast<PinType>(i);
    pin.state = LOW;
    pinStates.push_back(pin);
  }
}

void HUB75Connector::setPin(PinType type, PinState state) {
  pinStates[type].state = state;
  if (type == CLK && state == HIGH) {
    clockHigh();
  } else if (type == Latch && state == HIGH) {
    latchHigh();
  } else if (type == Latch && state == LOW) {
    latchLow();
  } else if (type == OE && state == HIGH) {
  }
}

void HUB75Connector::OEHigh() {
  // set the display to black
  display.setBufferRGB(std::vector<uint8_t>(WIDTH * HEIGHT * 3, 0));
}

void HUB75Connector::OELow() {
  // set the display to the buffer
  // display.updateTexture();
}

void HUB75Connector::print() {
  std::cout << "Pin states: " << std::endl;
  for (int i = 0; i < 13; i++) {
    std::cout << " | " << i << ":" << pinStates[i].state;
  }
  std::cout << std::endl;
  std::cout << "R1: " << RReg1 << std::endl;
  std::cout << "G1: " << GReg1 << std::endl;
  std::cout << "B1: " << BReg1 << std::endl;
  std::cout << "R2: " << RReg2 << std::endl;
  std::cout << "G2: " << GReg2 << std::endl;
  std::cout << "B2: " << BReg2 << std::endl;
}

PinState HUB75Connector::readPin(PinType type) { return pinStates[type].state; }

void HUB75Connector::clockHigh() { 
  // shift the data in the rgb pins into the 'registers',
  // (stores the state of the next scan)
  RReg1 = RReg1 << 1 ; RReg1.set(0, readPin(R1));
  GReg1 = GReg1 << 1 ; GReg1.set(0, readPin(G1));
  BReg1 = BReg1 << 1 ; BReg1.set(0, readPin(B1));
  RReg2 = RReg2 << 1 ; RReg2.set(0, readPin(R2));
  GReg2 = GReg2 << 1 ; GReg2.set(0, readPin(G2));
  BReg2 = BReg2 << 1 ; BReg2.set(0, readPin(B2));
}

void HUB75Connector::latchHigh() {
  print();
  // set the display buffer to the new data
  int row = getRow();
  // pulsing the latch pin replaces the displayed data with the data just input
  display.setBufferRow(row, RReg1, GReg1, BReg1);
  display.setBufferRow(row + (WIDTH / 2), RReg2, GReg2, BReg2);
}

void HUB75Connector::latchLow() {
  // reset the registers se we can store the data for the new position
  RReg1.reset();
  GReg1.reset();
  BReg1.reset();
  RReg2.reset();
  GReg2.reset();
  BReg2.reset();
}

int HUB75Connector::getRow() {
  // get the row number from the address pins
  int row = 0;
  for (int i = 0; i < 4; i++) {
    row |= readPin(static_cast<PinType>(i)) << i;
  }
  return row;
}