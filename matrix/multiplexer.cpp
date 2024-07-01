#include "multiplexer.h"

Multiplexer::Multiplexer() {
  data = 0;
  selectLine = 0;
}

void Multiplexer::setSelectLine(int line, bool value) {
  if (value) {
    selectLine |= 1 << line;
  } else {
    selectLine &= ~(1 << line);
  }
}

char Multiplexer::read() {
  return data;
}

void Multiplexer::print() {
  std::bitset<8> dataBits(data);
  std::bitset<8> selectLineBits(selectLine);
  std::cout << "Data: " << dataBits << " Select Line: " << selectLineBits << std::endl;
}