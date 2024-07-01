#include "matrix-display.h"

MatrixDisplay::MatrixDisplay(int rowBytes, int rows)
    : _rowBytes(rowBytes), _rows(rows), _display(rowBytes * rows) {}

void MatrixDisplay::setByte(int row, int idx, char byte) {
  _display[row * _rowBytes + idx] = byte;
}

void MatrixDisplay::print() {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _rowBytes; j++) {
      std::cout << _display[i * _rowBytes + j];
    }
    std::cout << std::endl;
  }
}