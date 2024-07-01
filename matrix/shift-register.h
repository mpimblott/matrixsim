#ifndef SHIFT_REGISTER_H
#define SHIFT_REGISTER_H

#include <bitset>
#include <iostream>

class RegisterSIPO {
public:
  RegisterSIPO();
  void setDataline(bool value);
  void clock();
  void clear();
  char read();
  void print();

private:
  bool dataLine;
  char data;
};

#endif