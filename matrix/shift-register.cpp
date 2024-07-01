#include "shift-register.h"

RegisterSIPO::RegisterSIPO() {
  data = 0b00000000;
}

void RegisterSIPO::clock() {
  data = data << 1 | dataLine;
}

void RegisterSIPO::setDataline(bool value) {
  dataLine = value;
}

void RegisterSIPO::clear() {
  data = 0b00000000;
}

char RegisterSIPO::read() {
  return data;
}

void RegisterSIPO::print() {
  std::cout << std::bitset<8>(data) << std::endl;
}