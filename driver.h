#ifndef DRIVER_H
#define DRIVER_H

#include <stdint.h>

#include <bitset>
#include <chrono>
#include <stdexcept>
#include <thread>
#include <vector>

#include "util.h"
#include "HUB75.h"
#include "imgBuffer.h"

enum colour { colour8, colour565, greyscale };

class MatrixDriver {
 public:
  MatrixDriver(HUB75Connector& connector, int shiftDelay = 10,
               colour colourMode = colour8);
  void setBuffer(std::vector<uint8_t> buffer);
  void loadRow(int row);
  void loadNextRow();
  std::bitset<WIDTH * N_SUBFRAMES> buildSubframeSequence(int buffer_idx);
  void setBrightness(int brightness);

 private:
  int brightness = 0;
  void clock();
  void latch();
  void setRowAddress(int row);
  HUB75Connector& connector;
  std::vector<uint8_t> internalBuffer;
  ImgBuffer displayBuffer;
  colour colourMode;
  int selectedRow = 0;
  int delay;
  void offDelay();
  void onDelay();
  int frameOrder[15] = {3,3,2,3,1,2,3,0,3,2,1,3,2,3,3};
  static int getSubframeBit(int frameNo);
};
#endif