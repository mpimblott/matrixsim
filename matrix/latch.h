#ifndef LATCH_H
#define LATCH_H

#include <iostream>
#include <bitset>

class Latch {
  public:
    Latch();
    void set(char value);
    char read();
    void print();

  private:
    char data;
};

#endif