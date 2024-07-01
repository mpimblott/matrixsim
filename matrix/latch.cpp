#include "latch.h"

Latch::Latch() {
  data = 0b00000000;
}

void Latch::set(char value) {
  data = value;
}

char Latch::read() {
  return data;
}

void Latch::print() {
  std::cout << std::bitset<8>(data) << std::endl;
}