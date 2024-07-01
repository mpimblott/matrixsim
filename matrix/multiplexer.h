#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H

#include <iostream>
#include <bitset>

class Multiplexer {
public:
  Multiplexer();
  void setSelectLine(int line, bool value);
  char read();
  void print();

private:
  char data;
  char selectLine;
};

#endif