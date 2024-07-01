#ifndef MATRIX_DISPLAY_H
#define MATRIX_DISPLAY_H

#include <iostream>
#include <vector>

class MatrixDisplay {
public:
  MatrixDisplay(int rowBytes, int rows);
  void setByte(int row, int idx, char byte);
  void print();

private:
  int _rowBytes;
  int _rows;
  std::vector<char> _display;
};

#endif