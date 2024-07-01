#ifndef DRIVER_H
#define DRIVER_H

#include <stdint.h>

#include <chrono>
#include <vector>
#include <thread>
#include <stdexcept>

#include "Hub75.h"

enum colour { colour8, colour565, greyscale };

class MatrixDriver {
 public:
  MatrixDriver(HUB75Connector& connector, int width = 64, int height = 64,
               int shiftDelay = 10, colour colourMode = colour8);
  void setBuffer(std::vector<uint8_t> buffer);
  void loadRow(int row);
  void loadNextRow();

 private:
  void clock();
  void latch();
  void setRowAddress(int row);
  HUB75Connector& connector;
  std::vector<uint8_t> displayBuffer;
  int width;
  int height;
  colour colourMode;
  int selectedRow = 0;
  std::chrono::milliseconds shiftDelay;
  uint8_t colourBytes();
  void delay();
};

#endif